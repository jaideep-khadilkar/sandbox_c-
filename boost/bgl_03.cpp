
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
void addNeighbor(int i1, int i2,MyGraphType& G,WeightMapType& weightmap,ppm&	image)
{
	  float sq = -0.5 * pow(float(image.g[i1])-float(image.g[i2]),2);
	  float B = exp(sq);
	  auto e1 = add_edge(i1,i2,G).first;
	  weightmap[e1] = B;
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
		  addNeighbor(i,i+1,G,weightmap,image);
//		  float sq = -1/2 * (image.g[i]-image.g[i+1])^2;
//		  float expVal = exp(sq);
//		  float B = expVal;
//
//		  auto e1 = add_edge(i,i+1,G).first;
//		  weightmap[e1] = B;
	  }
  }


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

  cout << "sampleCountFG : " << sampleCountFG << endl;
  cout << "sampleCountBG : " << sampleCountBG << endl;

  cout << "FG Histogram " << endl;
  for(int i=0;i<numLevels;i++)
  {
	  if(pdfFG[i]!=0)
	  cout << i << " : " << pdfFG[i] << endl;

  }
  cout << "BG Histogram " << endl;
  for(int i=0;i<numLevels;i++)
  {
	  if(pdfBG[i]!=0)
	  cout << i << " : " << pdfBG[i] << endl;
  }

  /*
   * Set Regional Weights
   */
  for(int i=0;i<size;i++)
  {
	  int data = int(image.g[i]);

	  auto e1 = add_edge(size,i,G).first;
	  weightmap[e1] = float(pdfFG[data])/float(sampleCountFG);

	  auto e2 = add_edge(size+1,i,G).first;
	  weightmap[e2] = float(pdfBG[data])/float(sampleCountBG);
  }

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
    image.r[currentVtxIndex] = get(parity,*iter) * 255;
    image.g[currentVtxIndex] = get(parity,*iter) * 255;
    image.b[currentVtxIndex] = get(parity,*iter) * 255;
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