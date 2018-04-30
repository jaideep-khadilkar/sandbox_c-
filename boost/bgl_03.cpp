
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/graph/one_bit_color_map.hpp>
#include "ppm.h"
#include <boost/timer.hpp>

using namespace std;

static const float sigma = 1.0;
static const float lambda = 0.0001;

struct VertexData
{
	int value;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS,
                              boost::undirectedS,
								VertexData,
                              boost::property<boost::edge_weight_t, double>
                              > MyGraphType;

typedef boost::property_map<MyGraphType, boost::edge_weight_t>::type WeightMapType;
float addNeighbor(int i1, int i2,MyGraphType& G,WeightMapType& weightmap,ppm&	image)
{
	  float sq = - pow(float(image.g[i1])-float(image.g[i2]),2)/float(2*pow(sigma,2));
	  float B = exp(sq);
	  auto e1 = add_edge(i1,i2,G).first;
	  weightmap[e1] = B;
	  return B;
}

void example0a()
{

	/*
	 * Read Image
	 */
	const int width = 64;
	const int height = 64;
	const int size = width * height;
	const int numLevels = 256;

	ppm	image("/home/user/git/sandbox_cpp/boost/apples_64.ppm");
	ppm	imageFGBG("/home/user/git/sandbox_cpp/boost/apples_64.ppm");
	ppm	imageN("/home/user/git/sandbox_cpp/boost/apples_64.ppm");

	/*
	 * Create Graph
	 */

  MyGraphType G(size+2);
  boost::property_map<MyGraphType, boost::edge_weight_t>::type weightmap =
    get(boost::edge_weight, G);

  /*
   * Set Neighboring Weights
   */
  for(int i=0;i<size;i++)
  {
	  if((i/width)==((i+1)/width))
	  {
		  float val = addNeighbor(i,i+1,G,weightmap,image);
		  imageN.r[i] = val * 255;
	  }
	  if((i+width)<size)
	  {
		  float val = addNeighbor(i,i+width,G,weightmap,image);
		  imageN.g[i] = val * 255;
	  }
	  int col = i%width;
	  int row = i/width;
	  if(col < (width-1) && row<(height-1))
	  {
		  float val = addNeighbor(i,i+width+1,G,weightmap,image);
		  imageN.b[i] = val * 255;
	  }
	  if(col>0 && row<(height-1))
	  {
		  addNeighbor(i,i+width-1,G,weightmap,image);
	  }
  }
//  cout << "K : " << K << endl;

  /*
   * Build Histogram & Probability Distribution Function
   */

  int pdfFG[numLevels] = {0};
  int pdfBG[numLevels] = {0};
  int sampleCountFG = 0;
  int sampleCountBG = 0;
  for(int i=0;i<size;i++)
  {
	  if(int(image.r[i]))
	  {
		  sampleCountFG++;
		  pdfFG[int(image.g[i])] = pdfFG[int(image.g[i])] + 1;
	  }
	  if(int(image.b[i]))
	  {
		  sampleCountBG++;
		  pdfBG[int(image.g[i])] = pdfBG[int(image.g[i])] + 1;
	  }
  }

  /*
   * Set Regional Weights
   */
  for(int i=0;i<size;i++)
  {
	  int data = int(image.g[i]);

	  /*
	   * FG
	   */
	  auto e1 = add_edge(size,i,G).first;
	  float weightFG = 0;
	  if(int(image.r[i]))
	  {
		  weightFG = 255;
	  }
	  else
	  {
		  float val = float(pdfBG[data])/float(sampleCountBG);
		  if(val<0.00001) val = 0.00001;
		  weightFG = -lambda * log(val);
//		  cout << " weightFG : " << weightFG << endl;
	  }
	  if(int(image.b[i]))
	  {
		  weightFG = 0;
	  }
	  weightmap[e1] = weightFG;
	  imageFGBG.r[i] = weightFG * 100;

	  /*
	   * BG
	   */
	  auto e2 = add_edge(size+1,i,G).first;
	  float weightBG = 0;
	  if(int(image.b[i]))
	  {
		  weightBG = 255;
	  }
	  else
	  {
		  float val = float(pdfFG[data])/float(sampleCountFG);
		  if(val<0.00001) val = 0.00001;
		  weightBG = -lambda * log(val);
//		  cout << " weightBG : " << weightBG << endl;
	  }
	  if(int(image.r[i]))
	  {
		  weightBG = 0;
	  }
	  weightmap[e2] = weightBG;
	  imageFGBG.b[i] = weightBG * 100;
  }

    imageFGBG.write("/home/user/git/sandbox_cpp/boost/apples_64_fgbg.ppm");
    imageN.write("/home/user/git/sandbox_cpp/boost/apples_64_n.ppm");

  /*
   * MinCut Algorithm
   */
  auto parity = boost::make_one_bit_color_map(num_vertices(G), get(boost::vertex_index, G));
  float mincut = boost::stoer_wagner_min_cut(G, weightmap, boost::parity_map(parity));
  auto vpair = vertices(G);

  /*
   * Write Out The Segmented Image
   */
  int currentVtxIndex = 0;
  for(auto iter=vpair.first; iter!=vpair.second; iter++) {

	  cout << currentVtxIndex << " : " << get(parity,*iter) << endl;

//    image.r[currentVtxIndex] = image.g[currentVtxIndex] + get(parity,*iter) * 100;
    image.r[currentVtxIndex] = get(parity,*iter) * 255;
//    image.g[currentVtxIndex] = get(parity,*iter) * 255;
//    image.b[currentVtxIndex] = image.g[currentVtxIndex] + (1-get(parity,*iter)) * 100;
    image.b[currentVtxIndex] = (1-get(parity,*iter)) * 255;
    currentVtxIndex++;
  }
  image.write("/home/user/git/sandbox_cpp/boost/apples_64_seg.ppm");

}


int
main(int, char *[])
{
  boost::timer t; // start timing
  example0a();
  cout << t.elapsed() << endl;
}
