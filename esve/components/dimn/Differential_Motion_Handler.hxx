
#ifndef esve_components_dimn_Differential_Motion_Handler_hxx
#define esve_components_dimn_Differential_Motion_Handler_hxx

#include <esve/components/dimn/Supermouse_Motion_Handler.hxx>
#include <esve/types/pure.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Differential_Motion_Handler esve/components/dimn/Differential_Motion_Handler.hxx
/// @brief Common base class for defining motion via differentials.
///
/// The buttons yield parented motion: the left button is grandpa, the
/// middle is pa, and the right is baby.
///

template< typename Transform >
class Differential_Motion_Handler
    : public Supermouse_Motion_Handler
{
private:
    typedef Supermouse_Motion_Handler super ;

    struct m_Button_Data
    {
        // the basis in which the motion is created
        const Transform* basis ;

        // for each motion we keep the transform from which it came
        Transform motion_basis ;

        // mini frame hierarchy
        Transform frame ;

        // whether motion is on
        bool go ;

        m_Button_Data() ;

    private:
        m_Button_Data( const m_Button_Data & ) ;
        m_Button_Data & operator=( const m_Button_Data & ) ;
    } ;

    Differential_Motion_Handler( const Differential_Motion_Handler & ) ;
    Differential_Motion_Handler &
    operator=( const Differential_Motion_Handler & ) ;

    Transform* m_transform ;
    Transform m_root ;
    m_Button_Data m_button[Supermouse::NUM_BUTTONS] ;
    double m_dt_since_drag ;
    bool m_reset_frames ;

public:
    /// Constructor.  Give the transform on which this handler operates
    explicit Differential_Motion_Handler( Transform & ) ;

    ///@{
    ///
    /// @brief The transform on which this handler operates.
    ///
    void active_transform( Transform & ) ;

    const Transform & active_transform() const
    {
        return *m_transform ;
    }
    ///@}

    ///@{
    /// @brief The basis in which the motion is created, for this button.
    /// The basis is stored by reference.
    const Transform & basis( Button ) const ;
    void basis( Button, const Transform & basis ) ;
    ///@}

    void stop() ;

    void update( double dt ) ;
    using super::update ;

    ~Differential_Motion_Handler() ;

protected:
    bool handle_supermouse_push( Button, const Supermouse & ) ;
    bool handle_supermouse_release( Button, const Supermouse & ) ;
    bool handle_check_awake( bool currently_awake ) ;

    ///
    /// @brief Create and store motion data in the subclass.
    ///
    /// Units of du_dt are pixels per second, already adjusted for
    /// sensitivity.
    ///
    virtual void create_motion( Button, const types::pure & du_dt ) = 0 ;

    ///
    /// @brief Return the differential action corresponding to this time
    /// differential (in seconds).
    ///
    virtual Transform differential_motion( Button, types::real dt ) = 0 ;

    /// Set subclass' motion data to zero velocity.
    virtual void stop_motion( Button ) = 0 ;

    /// Whether subclass' motion data indicates nonzero velocity.
    virtual bool has_motion( Button ) = 0 ;

    ///
    /// @brief Hook to normalize (or not) after a differential action.
    ///
    /// Default calls transform.normalize()
    ///
    virtual void normalize( Transform & transform ) ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Differential_Motion_Handler.template.cxx>

#endif

