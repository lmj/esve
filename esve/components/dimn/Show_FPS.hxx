
#ifndef esve_components_dimn_Show_FPS_hxx
#define esve_components_dimn_Show_FPS_hxx

#include <esve/message/impl/Update_Receiver.hxx>
#include <iosfwd>

namespace esve { namespace components { namespace dimn {

///
/// @class Show_FPS esve/components/dimn/Show_FPS.hxx
/// @brief Show frames per second.
///
/// Write frames per second to an output stream, counting every
/// sampling_interval() seconds.
///

class Show_FPS
    : virtual public message::impl::Update_Receiver
{
public:
    Show_FPS() ;

    ///@{
    ///
    /// @brief Time interval (in seconds) in which to count frames.
    ///
    double sampling_interval() const
    {
        return m_sampling_interval ;
    }

    void sampling_interval( double ) ;
    ///@}

    ///@{
    /// @brief Where to send the output (default stderr).
    const std::ostream & output() const ;
    void output( std::ostream & ) ;
    ///@}

    ~Show_FPS() ;

protected:
    void update() ;
    void update( double dt ) ;
    
private:
    Show_FPS( const Show_FPS & ) ;
    Show_FPS & operator=( const Show_FPS & ) ;

    double m_sampling_interval ;
    double m_elapsed ;
    int m_visit ;
    std::ostream* m_output ;
} ;

}}} // namespace esve::components::dimn

#endif

