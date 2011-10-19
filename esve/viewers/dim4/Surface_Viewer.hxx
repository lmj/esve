
#ifndef esve_viewers_dim4_Surface_Viewer_hxx
#define esve_viewers_dim4_Surface_Viewer_hxx

#include <esve/viewers/dim4/Surface_Viewer_Spec.hxx>
#include <esve/viewers/dimn/Surface_Viewer.hxx>
#include <string>

namespace esve { namespace viewers { namespace dim4 {

template< typename T_Surface_Spec >
class Surface_Viewer
    : public viewers::dimn::Surface_Viewer
             <
                 Surface_Viewer_Spec<T_Surface_Spec>
             >
{
private:
    typedef
    viewers::dimn::Surface_Viewer
             <
                 Surface_Viewer_Spec<T_Surface_Spec>
             >
    super ;

    Surface_Viewer( const Surface_Viewer & ) ;
    Surface_Viewer & operator=( const Surface_Viewer & ) ;

public:
    Surface_Viewer( int argc,
                    char** argv,
                    const std::string & name = "surface viewer" ) ;

    ~Surface_Viewer() ;
} ;

}}} // namespace esve::viewers::dim4

#include <esve/viewers/dim4/Surface_Viewer.template.cxx>

#endif

