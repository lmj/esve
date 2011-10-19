
#include "Tope_File.hxx"

Tope_File::
Tope_File()
{
}

Tope_File::
~Tope_File()
{
}

Tope_File::
Error::
Error( const std::string & what,
       const std::string & filename_ )
    : std::runtime_error(what),
      filename(filename_)
{
}

Tope_File::
Read_Error::
Read_Error( const std::string & filename )
    : Error("error reading tope file: " + filename,
            filename)
{
}

Tope_File::
Write_Error::
Write_Error( const std::string & filename_ )
    : Error("error writing tope file: " + filename_,
            filename)
{
}

Tope_File::
Error::
~Error() throw()
{
}

Tope_File::
Read_Error::
~Read_Error() throw()
{
}

Tope_File::
Write_Error::
~Write_Error() throw()
{
}

