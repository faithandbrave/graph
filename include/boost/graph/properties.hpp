//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, University of Notre Dame, Notre
// Dame, IN 46556.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================
#ifndef BOOST_GRAPH_PROPERTIES_HPP
#define BOOST_GRAPH_PROPERTIES_HPP

#include <boost/config.hpp>
#include <boost/property_accessor.hpp>

namespace boost {

  enum default_color_type { white_color, gray_color, black_color };

  inline default_color_type white(default_color_type) { return white_color; }
  inline default_color_type gray(default_color_type) { return gray_color; }
  inline default_color_type black(default_color_type) { return black_color; }

  namespace detail {
    // These enums are only used in the no partial specialzation workaround
    enum property_tag_num
    {
      NO_PLUGIN_TAG, ID_PLUGIN_TAG, NAME_PLUGIN_TAG, WEIGHT_PLUGIN_TAG, 
      DISTANCE_PLUGIN_TAG, COLOR_PLUGIN_TAG, DEGREE_PLUGIN_TAG,
      OUT_DEGREE_PLUGIN_TAG, IN_DEGREE_PLUGIN_TAG, DISCOVER_TIME_PLUGIN_TAG,
      FINISH_TIME_PLUGIN_TAG
    };
  } // namespace detail

  // The enum's are only necessary for a workaround for compilers that
  // don't do partial specialization (like VC++).

  struct vertex_index {
    enum { num = detail::ID_PLUGIN_TAG };
  };
  struct graph_name { 
    enum { num = detail::NAME_PLUGIN_TAG };
  };
  struct vertex_name { 
    enum { num = detail::NAME_PLUGIN_TAG };
  };
  struct edge_name { 
    enum { num = detail::NAME_PLUGIN_TAG };
  };
  struct edge_weight { 
    enum { num = detail::WEIGHT_PLUGIN_TAG };
  };
  struct vertex_distance { 
    enum { num = detail::DISTANCE_PLUGIN_TAG };
  };
  struct vertex_color { 
    enum { num = detail::COLOR_PLUGIN_TAG };
  };
  struct vertex_degree { 
    enum { num = detail::DEGREE_PLUGIN_TAG };
  };
  struct vertex_out_degree { 
    enum { num = detail::OUT_DEGREE_PLUGIN_TAG };
  };
  struct vertex_in_degree { 
    enum { num = detail::IN_DEGREE_PLUGIN_TAG };
  };
  struct vertex_discover_time { 
    enum { num = detail::DISCOVER_TIME_PLUGIN_TAG };
  };
  struct vertex_finish_time { 
    enum { num = detail::FINISH_TIME_PLUGIN_TAG };
  };

  struct foo_edge_property_selector {
    template <class Graph, class Plugin, class Tag>
    struct bind {
      typedef void type;
      typedef void const_type;
    };
  };
  template <class GraphTag>
  struct edge_property_selector {
    typedef foo_edge_property_selector type;
  };

  struct foo_vertex_property_selector {
    template <class Graph, class Plugin, class Tag>
    struct bind {
      typedef void type;
      typedef void const_type;
    };
  };

  template <class GraphTag>
  struct vertex_property_selector {
    typedef foo_vertex_property_selector type;
  };

  template <class Graph, class PropertyTag>
  struct edge_property_accessor {
    typedef typename Graph::directed_category Directed;
    typedef typename Graph::edge_plugin_type Plugin;
    typedef typename Graph::graph_tag graph_tag;
    typedef typename edge_property_selector<graph_tag>::type Selector;
    typedef typename Selector::template bind<Graph,Plugin,PropertyTag>
      Bind;
    typedef typename Bind::type type;
    typedef typename Bind::const_type const_type;
  };
  template <class Graph, class PropertyTag>
  class vertex_property_accessor {
    typedef typename Graph::vertex_plugin_type Plugin;
    typedef typename Graph::graph_tag graph_tag;
    typedef typename vertex_property_selector<graph_tag>::type Selector;
    typedef typename Selector::template bind<Graph,Plugin,PropertyTag>
      Bind;
  public:
    typedef typename Bind::type type;
    typedef typename Bind::const_type const_type;
  };


} // namespace boost

#endif /* BOOST_GRAPH_PROPERTIES_HPPA */
