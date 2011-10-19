#!/usr/bin/ruby

help = File.open("help_text.txt").read.split(/\n/).map { |e|
   e.chomp.gsub(%r{\"}, %q{\\\"}) + %q{\\n\\} + "\n"
}.join

File.open("help_text.cxx", "w").print <<EOS
#include "help_text.hxx"

const std::string HELP_TEXT =
"#{help}" ;

const std::string & help_text()
{
    return HELP_TEXT ;
}

EOS

