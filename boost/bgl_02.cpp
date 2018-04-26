
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>

struct EdgeData
{
  std::string edge_name;
  double dist;
};

void example0a()
{
  typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                boost::undirectedS,
                                boost::no_property,
                                boost::property<boost::edge_weight_t, double>
                                > MyGraphType;
  MyGraphType G(11);
  boost::property_map<MyGraphType, boost::edge_weight_t>::type weightmap =
    get(boost::edge_weight, G);

  for(int i=0;i<10;i++)
  {
	  auto e = add_edge(i,i+1,G).first;
	  weightmap[e] = i;
	  std::cout << "saved weight " << weightmap[e] << std::endl;
  }

}


int
main(int, char *[])
{
  example0a();
}
