
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/graph/one_bit_color_map.hpp>
#include "ppm.h"

struct VertexData
{
	int value;
};

void example0a()
{
	const int width = 64;
	const int height = 64;
	const int size = width * height;
	const int numLevels = 256;

	ppm	image("/home/user/git/sandbox_cpp/boost/apples_64.ppm");

  typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                boost::undirectedS,
								VertexData,
                                boost::property<boost::edge_weight_t, double>
                                > MyGraphType;
  MyGraphType G(size+2);
  boost::property_map<MyGraphType, boost::edge_weight_t>::type weightmap =
    get(boost::edge_weight, G);

  int pdfFG[numLevels];
  int pdfBG[numLevels];
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

  for(int i=0;i<numLevels;i++)
  {
	  if(sampleCountFG!=0)
	  {
		  pdfFG[i] = pdfFG[i]/sampleCountFG;
	  }
	  if(sampleCountBG!=0)
	  {
		  pdfBG[i] = pdfBG[i]/sampleCountBG;
	  }
  }

  for(int i=0;i<size;i++)
  {
	  int data = int(image.g[i]);
	  auto e1 = add_edge(size,i,G).first;
	  weightmap[e1] = 1 - float(abs(data-255))/float(255);

	  auto e2 = add_edge(size+1,i,G).first;
	  weightmap[e2] = 1 - float(abs(data-0))/float(255);

  }

  auto parity = boost::make_one_bit_color_map(num_vertices(G), get(boost::vertex_index, G));
  float mincut = boost::stoer_wagner_min_cut(G, weightmap, boost::parity_map(parity));
  auto vpair = vertices(G);

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
  example0a();
}
