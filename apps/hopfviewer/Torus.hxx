//
// The Clifford torus in standard coordinates.
//

#ifndef apps_hopfviewer_Torus_hxx
#define apps_hopfviewer_Torus_hxx

#include <esve/base/dimn/vertex/CNTP_Vertex.hxx>
#include <esve/util/member_iterator.hxx>
#include <esve/types/rgba.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>
#include <vector>
#include <cstddef>

class Torus
{
public:
    ////////////////////////////////////////////////
    // types
    
    typedef std::size_t size_type ;

    ////////////////////////////////////////////////
    // constructor
    Torus() ;
    
    ////////////////////////////////////////////////
    // compiler writes memberwise copy and assign

    ////////////////////////////////////////////////
    // The sin and cos of this angle are the radii of the two
    // generating circles.

    double ratio_angle() const
    {
        return m_ratio_angle ;
    }

    void ratio_angle( double a )
    {
        m_write_param(&m_ratio_angle, a) ;
    }

    ////////////////////////////////////////////////
    // how many points along width/height

    size_type width_res() const
    {
        return m_width_res ;
    }

    void width_res( size_type a )
    {
        m_write_param(&m_width_res, a) ;
    }

    size_type height_res() const
    {
        return m_height_res ;
    }

    void height_res( size_type a )
    {
        m_write_param(&m_height_res, a) ;
    }

    ////////////////////////////////////////////////
    // fraction of domain showing (between 0 and resolution)

    double width() const
    {
        return m_width ;
    }

    void width( double a )
    {
        m_write_param(&m_width, a) ;
    }

    double height() const
    {
        return m_height ;
    }

    void height( double a )
    {
        m_write_param(&m_height, a) ;
    }

    ////////////////////////////////////////////////
    // tilting effect of quads -- between 0 and 1

    double gap() const
    {
        return m_gap ;
    }

    void gap( double a )
    {
        m_write_param(&m_gap, a) ;
    }

    ////////////////////////////////////////////////
    // skew the domain

    double skew() const
    {
        return m_skew ;
    }

    void skew( double a )
    {
        m_write_param(&m_skew, a) ;
    }

    ////////////////////////////////////////////////
    // winding. the effective slope of the domain

    double wind_u() const
    {
        return m_wind_u ;
    }

    void wind_u( double a )
    {
        m_write_param(&m_wind_u, a) ;
    }

    double wind_v() const
    {
        return m_wind_v ;
    }

    void wind_v( double a )
    {
        m_write_param(&m_wind_v, a) ;
    }

    virtual ~Torus() ;

private:
    //////////////////////////////////////////////
    // private

    typedef
    esve::base::dimn::vertex::CNTP_Vertex
    <
        esve::types::rgba,   // color
        esve::types::pure,   // normal
        esve::types::quat,   // transformed_point
        esve::types::quat    // point
    >
    m_Vertex ;

    typedef std::vector<m_Vertex> m_Vertices ;
    typedef m_Vertices::iterator m_Vertices_iterator ;
    typedef m_Vertices::const_iterator m_Vertices_const_iterator ;

    void m_write_param( double* v, double a ) ;
    void m_write_param( size_type* v, size_type a ) ;
    void m_compute_torus() ;
    void m_compute_normals() ;

    m_Vertices m_vertices ;

    double m_ratio_angle ;
    size_type m_width_res ;
    size_type m_height_res ;
    double m_width ;
    double m_height ;
    double m_gap ;
    double m_skew ;
    double m_wind_u ;
    double m_wind_v ;

    bool m_need_compute ;

protected:
    ////////////////////////////////////////////////
    // OpenGL drawing routine
    virtual void draw() ;

    ////////////////////////////////////////////////
    //
    // Vertices_iterator provided for subclasses overriding draw().
    //
    // This is just a straight list of quads.
    //

    typedef m_Vertex Vertex ;
    typedef m_Vertices_iterator Vertices_iterator ;
    typedef m_Vertices_const_iterator Vertices_const_iterator ;

    Vertices_const_iterator vertices_begin() const
    {
        return m_vertices.begin() ;
    }

    Vertices_const_iterator vertices_end() const
    {
        return m_vertices.end() ;
    }

    Vertices_iterator vertices_begin()
    {
        return m_vertices.begin() ;
    }

    Vertices_iterator vertices_end()
    {
        return m_vertices.end() ;
    }

    ////////////////////////////////////////////////
    // The following are hooks into the Moebius frame system.
    // See Make_Frame.hxx.

    typedef
    esve::util::member_iterator< m_Vertices_const_iterator,
                                 const m_Vertex::Point,
                                 &m_Vertex::point >
    Points_iterator ;

    typedef
    esve::util::member_iterator< m_Vertices_iterator,
                                 m_Vertex::Transformed_Point,
                                 &m_Vertex::transformed_point >
    Transformed_Points_iterator ;

    Points_iterator points_begin() const
    {
        return Points_iterator(m_vertices.begin()) ;
    }

    Points_iterator points_end() const
    {
        return Points_iterator(m_vertices.end()) ;
    }

    Transformed_Points_iterator transformed_points_begin()
    {
        return Transformed_Points_iterator(m_vertices.begin()) ;
    }

    virtual bool changed() const ;
    virtual void pretransform() ;
    virtual void posttransform() ;
} ;

#endif

