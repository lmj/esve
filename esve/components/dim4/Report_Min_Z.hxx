
#ifndef esve_components_dim4_Report_Min_Z_hxx
#define esve_components_dim4_Report_Min_Z_hxx

#include <esve/components/dim3/Min_Z.hxx>
#include <esve/engine/dim4/Make_Frame.hxx>
#include <esve/types/quat.hxx>
#include <esve/util/misc.hxx>

namespace esve { namespace components { namespace dim4 {

///
/// @class Report_Min_Z esve/components/dim4/Report_Min_Z.hxx
/// @brief Reports the minimum transformed z-value of a frame.
///

template< typename T_Frame >
class Report_Min_Z
    : virtual public components::dim3::Min_Z,
      public T_Frame
{
private:
#if !defined(NDEBUG)
    void m_requirements_1()
    {
        typedef typename T_Frame::Make_Frame_Parameter_Target Target ;
        typedef typename T_Frame::Make_Frame_Parameter_Frame Frame ;

        engine::dim4::Make_Frame<Target, Frame>* r =
            util::misc::implicit_cast<T_Frame*>(this) ;
        util::misc::unused(r) ;
    }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef void (Report_Min_Z::*R)() ;
            R r = &Report_Min_Z::m_requirements_1 ;
            util::misc::unused(r) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)
    
    struct m_Find_Min
    {
        types::real min_z ;

        m_Find_Min( types::real min_z_ )
            : min_z(min_z_) { }

        void operator()( const types::quat & a )
        {
            if( a.z() < min_z )
            {
                min_z = a.z() ;
            }
        }
    } ;

    struct Private
    {
        types::real initial_min_z ;
        types::real min_z ;

        Private() ;
    } ;

    Report_Min_Z( const Report_Min_Z & ) ;
    Report_Min_Z & operator=( const Report_Min_Z & ) ;

    Private m ;

public:
    /// Default Constructor.
    Report_Min_Z() ;

    /// Construct T_Frame with an arbitrary argument.
    template< typename T_Arg >
    Report_Min_Z( T_Arg & ) ;

    /// Construct T_Frame with an arbitrary argument.
    template< typename T_Arg >
    Report_Min_Z( const T_Arg & ) ;

    types::real min_z() const
    {
        return m.min_z ;
    }

    ///@{
    ///
    /// @brief Optimize by setting an initial minimum.
    /// min_z() will never be greater than this value.
    ///
    types::real initial_min_z() const
    {
        return m.initial_min_z ;
    }

    void initial_min_z( types::real a )
    {
        m.initial_min_z = a ;
    }
    ///@}

    ~Report_Min_Z() ;

protected:
    /// Base class override.
    void apply_transform() ;
} ;

}}} // namespace esve::components::dim4

#include <esve/components/dim4/Report_Min_Z.template.cxx>

#endif

