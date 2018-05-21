#include "../SDP_Solver.hxx"
#include "../../Timers.hxx"

#include <boost/archive/text_oarchive.hpp>

namespace
{
  void backup_checkpoint_file(const boost::filesystem::path &checkpoint_file)
  {
    boost::filesystem::path backup_file(checkpoint_file);
    backup_file.replace_extension(".ck.bk");
    std::cout << "Backing up checkpoint to: " << backup_file << '\n';
    copy_file(checkpoint_file, backup_file,
              boost::filesystem::copy_option::overwrite_if_exists);
  }
}

void SDP_Solver::save_checkpoint(const boost::filesystem::path &checkpoint_file)
{
  if(exists(checkpoint_file))
    {
      backup_checkpoint_file(checkpoint_file);
    }
  boost::filesystem::ofstream ofs(checkpoint_file);
  boost::archive::text_oarchive ar(ofs);
  std::cout << "Saving checkpoint to    : " << checkpoint_file << '\n';
  // boost::serialization::serialize_SDP_solver_state(ar, x_elemental, X,
  //                                                  y_elemental, Y);
  timers["Last checkpoint"].start();
}
