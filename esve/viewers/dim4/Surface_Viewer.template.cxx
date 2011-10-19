
#include <esve/viewers/dim4/Surface_Viewer.hxx>

namespace esve { namespace viewers { namespace dim4 {

template< typename T_Surface_spec >
Surface_Viewer<T_Surface_spec>::
Surface_Viewer( int argc,
                char** argv,
                const std::string & name )
    : super(argc, argv, name)
{
}

template< typename T_Surface_spec >
Surface_Viewer<T_Surface_spec>::
~Surface_Viewer()
{
}

}}} // namespace esve::viewers::dim4
