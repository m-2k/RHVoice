/* Copyright (C) 2013  Olga Yakovleva <yakovleva.o.v@gmail.com> */

/* This program is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU Lesser General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public License */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef RHVOICE_MAGE_HTS_ENGINE_IMPL_HPP
#define RHVOICE_MAGE_HTS_ENGINE_IMPL_HPP

#include <memory>
#include <utility>
#include "hts_engine_impl.hpp"

namespace MAGE
{
  class Mage;
}

struct _HTS106_Vocoder;

namespace RHVoice
{
  class mage_hts_engine_impl: public hts_engine_impl
  {
  public:
    explicit mage_hts_engine_impl(const std::string& voice_path);

  private:
    class model_file_list
    {
    public:
      model_file_list(const std::string& voice_path,const std::string& type,int num_windows_=0);

      char* pdf;
      char* tree;
      int num_windows;
      char* windows[3];

    private:
      model_file_list(const model_file_list&);
      model_file_list& operator=(const model_file_list&);

      std::vector<std::string> file_names;
    };

     typedef std::pair<std::string,std::string> arg;
    typedef std::vector<arg> arg_list;

    pointer do_create() const;
    void do_initialize();
    void do_reset();
    void do_synthesize();

    void setup();
    void generate_parameters(hts_label& lab);
    void skip_initial_pause();
    void generate_samples(hts_label& lab);
    void append_model_args(arg_list& args,const model_file_list& files,const std::string& tree_arg_name,const std::string& pdf_arg_name,const std::string& win_arg_name="") const;

    std::auto_ptr<MAGE::Mage> mage;
    std::auto_ptr<_HTS106_Vocoder> vocoder;
  };
}
#endif
