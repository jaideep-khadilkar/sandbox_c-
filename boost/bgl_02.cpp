
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/graph/one_bit_color_map.hpp>

struct VertexData
{
	int value;
};

void example0a()
{

	int imageData[9];
	imageData[0] = 100;
	imageData[1] = 90;
	imageData[2] = 10;
	imageData[3] = 90;
	imageData[4] = 80;
	imageData[5] = 05;
	imageData[6] = 80;
	imageData[7] = 10;
	imageData[8] = 0;

	float tLinkFG[9];
	float tLinkBG[9];
	for(int i=0;i<9;i++)
	{
		tLinkFG[i] = 1 - float(abs(imageData[i]-100))/float(100);
		tLinkBG[i] = 1 - float(abs(imageData[i]-0))/float(100);
	}

  typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                boost::undirectedS,
								VertexData,
                                boost::property<boost::edge_weight_t, double>
                                > MyGraphType;
  MyGraphType G(11);
  boost::property_map<MyGraphType, boost::edge_weight_t>::type weightmap =
    get(boost::edge_weight, G);

  for(int i=0;i<9;i++)
  {
	  auto e1 = add_edge(9,i,G).first;
	  weightmap[e1] = tLinkFG[i];
	  std::cout << "FG : " << weightmap[e1] << std::endl;

	  auto e2 = add_edge(10,i,G).first;
	  weightmap[e2] = tLinkBG[i];
	  std::cout << "BG : " << weightmap[e2] << std::endl;

  }

  auto parity = boost::make_one_bit_color_map(num_vertices(G), get(boost::vertex_index, G));
  float mincut = boost::stoer_wagner_min_cut(G, weightmap, boost::parity_map(parity));
  auto vpair = vertices(G);
  for(auto iter=vpair.first; iter!=vpair.second; iter++) {
    std::cout << "Parity " << get(parity,*iter) << std::endl;
  }


}


int
main(int, char *[])
{
  example0a();
}
