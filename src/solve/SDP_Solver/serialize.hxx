//=======================================================================
// Copyright 2014-2015 David Simmons-Duffin.
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#pragma once

#include "../Block_Diagonal_Matrix.hxx"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/filesystem.hpp>

#include <sstream>
#include <string>

namespace boost
{
  namespace serialization
  {
    template <class Archive> void load(Archive &ar, Real &f, unsigned int)
    {
      std::string s;
      ar &s;
      f = Real(s.c_str());
    }

    template <class Archive>
    void save(Archive &ar, Real const &f, unsigned int)
    {
      std::ostringstream os;
      os.precision(f.get_prec());
      os << f;
      std::string s = os.str();
      ar &s;
    }

    template <class Archive>
    void serialize(Archive &ar, Matrix &m, const unsigned int)
    {
      ar &m.rows;
      ar &m.cols;
      ar &m.elements;
    }

    template <class Archive>
    void serialize(Archive &ar, Block_Diagonal_Matrix &m, const unsigned int)
    {
      ar &m.dim;
      ar &m.blocks;
      ar &m.block_start_indices;
    }

    template <class Archive>
    void serialize_SDP_solver_state(Archive &ar, Vector &x,
                                    Block_Diagonal_Matrix &X, Vector &y,
                                    Block_Diagonal_Matrix &Y)
    {
      ar &x;
      ar &X;
      ar &y;
      ar &Y;
    }

  } // namespace serialization
} // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(Real)
BOOST_CLASS_VERSION(Real, 0)
BOOST_CLASS_TRACKING(Matrix, boost::serialization::track_never)
BOOST_CLASS_TRACKING(Block_Diagonal_Matrix, boost::serialization::track_never)
