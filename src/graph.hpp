#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <iterator>
#include <functional>
		

namespace mf
{

template<typename DataType>
class GraphNode
{
  public:
    GraphNode(DataType d, std::string name) : m_name(std::move(name)),
                                              m_data(std::move(d))
    {}

    DataType data() const {return m_data;}
    std::string name() const {return m_name;}
    const std::vector<std::reference_wrapper<GraphNode<DataType>>>& followers() const {return m_followers;}
    std::vector<std::reference_wrapper<GraphNode<DataType>>>& followers() {return m_followers;}

  private:
    std::string m_name;
    DataType m_data;
    std::vector<std::reference_wrapper<GraphNode<DataType>>> m_followers;
};



template<typename DataType>
class Graph
{
  public:
    Graph()
    {}

    void add_node(const std::string name, DataType data = {})
    {
        m_nodes.insert({std::move(name), GraphNode<DataType>(data, name)});
    }

    void add_edge(const std::string& node_1, const std::string& node_2)
    {
        if(m_nodes.find(node_1) == std::end(m_nodes))
        {
            throw std::runtime_error("There is no node in the graph with tha name");
        }

        if(m_nodes.find(node_2) == std::end(m_nodes))
        {
            throw std::runtime_error("There is no node in the graph with tha name");
        }
        
        m_nodes.at(node_1).followers().emplace_back(std::ref(m_nodes.at(node_2)));
        
    }

    std::vector<DataType> get_following_edges(const std::string& node) const
    {
        if(m_nodes.find(node) == std::end(m_nodes))
        {
            throw std::runtime_error("There is no node in the graph with tha name");
        }

        std::vector<DataType> res;
        auto& following_nodes = m_nodes.at(node).followers();
        std::transform(std::begin(following_nodes),
                       std::end(following_nodes),
                       std::back_insert_iterator(res),
                       [](const GraphNode<DataType>& node){return node.data();});
        
        return res;
    }

    DataType get_node_data(const std::string& node)
    {
        if(m_nodes.find(node) == std::end(m_nodes))
        {
            throw std::runtime_error("There is no node in the graph with tha name");
        }
        return m_nodes.at(node).data();
    }

  private:
    std::unordered_map<std::string, GraphNode<DataType>> m_nodes;
};





}
