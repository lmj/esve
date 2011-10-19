
#ifndef esve_engine_dim4_Make_Frame_hxx
#define esve_engine_dim4_Make_Frame_hxx

#include <esve/engine/dim4/impl/Frame.hxx>
#include <esve/engine/dim4/Transform.hxx>
#include <esve/message/impl/Compute_Receiver.hxx>
#include <esve/types/quat.hxx>
#include <esve/util/misc.hxx>

namespace esve { namespace engine { namespace dim4 {

///
/// @class Make_Frame esve/engine/dim4/Make_Frame.hxx
/// @brief Make a class into a Frame.
///
/// The target class must provide the following:
/// @code
/// class Your_Class
/// {
/// public:
///    // ...
///
/// protected:
///    // Input iterator for the untransformed points.
///    // The iterator may be anything which dereferences to quat.
///    input_iterator points_begin() const ;
///    input_iterator points_end() const ;
///
///    // Output iterator for the transformed points.
///    // The iterator may be anything which dereferences to quat.
///    output_iterator transformed_points_begin() ;
///
///    // Return true if any points have been moved.
///    // The system will re-apply the transform.
///    virtual bool changed() const ;
///
///    // Called just before the transform is applied.
///    // This is where points should be updated, if needed.
///    virtual void pretransform() ;
///
///    // Called just after the transform is applied.
///    // Compute normals here.
///    virtual void posttransform() ;
///
///    // ...
///
/// private:
///    // ...
/// } ;
/// @endcode
///
/// When these methods are provided, the statement
/// @code
///    engine::dim4::Make_Frame<Your_Class> your_object ;
/// @endcode
/// will construct an object with a Moebius frame attached.
///
/// If Your_Class cannot be default-constructed, you have the
/// option of giving Make_Frame one argument which is passed
/// along to the constructor of Your_Class.
///
/// Make_Frame also makes the class a member of the compute tree,
/// replacing compute() with the pretransform() and posttransform()
/// virtual hooks.
///
/// The transform must be hooked up to a compute() message sender.
/// Front-ends which have an add_geom() method will take care of this
/// automatically.  Otherwise you must establish computation order by
/// adding the transform to a message::Compute_Sender such as a
/// camera.  See message::Compute_Receiver.
///

template< typename T_Target, typename T_Frame = impl::Frame >
class Make_Frame
    : virtual public message::impl::Compute_Receiver,
      public T_Frame,
      public T_Target
{
private:
#if !defined(NDEBUG)
    void m_requirements_1() const
    {
        bool r = T_Target::changed() ;
        util::misc::unused(r) ;
    }

    void m_requirements_2()
    {
        T_Target::pretransform() ;
        T_Target::posttransform() ;

        m_requirements_2_1(T_Target::points_begin()) ;
        m_requirements_2_1(T_Target::points_end()) ;
        m_requirements_2_2(T_Target::transformed_points_begin()) ;

        engine::dim4::Frame* r = util::misc::implicit_cast<T_Frame*>(this) ;
        util::misc::unused(r) ;
    }

    template< typename T_Points_iterator >
    void m_requirements_2_1( T_Points_iterator i )
    {
        types::quat q = *i ;
        ++i ;
    }

    template< typename T_Transformed_Points_iterator >
    void m_requirements_2_2( T_Transformed_Points_iterator i )
    {
        *i = types::quat() ;
        ++i ;
    }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef void (Make_Frame::*R1)() const ;
            typedef void (Make_Frame::*R2)() ;
            
            R1 r1 = &Make_Frame::m_requirements_1 ;
            R2 r2 = &Make_Frame::m_requirements_2 ;
            util::misc::unused(r1) ;
            util::misc::unused(r2) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)

    struct Private
    {
        bool initialized ;
        Transform last_world_transform ;

        Private() ;
    } ;

    Make_Frame( const Make_Frame & ) ;
    Make_Frame & operator=( const Make_Frame & ) ;

    Private m ;

public:
    /// Default constructor.
    Make_Frame() ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Frame( T_Arg & ) ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Frame( const T_Arg & ) ;

    ~Make_Frame() ;

protected:
    typedef T_Target Make_Frame_Parameter_Target ;
    typedef T_Frame Make_Frame_Parameter_Frame ;
    
    void compute() ;

    /// Virtual hook to subclasses.  Recompute untransformed points, if needed.
    virtual void pretransform() ;

    /// @brief Virtual hook to subclasses.  Do something with the transformed
    /// points (such as computing normals).
    virtual void posttransform() ;

    /// @brief Virtual hook to subclasses.  Whether untransformed
    /// points have changed.
    virtual bool changed() const ;

    /// Transform the points.
    virtual void apply_transform() ;
} ;

}}} // namespace esve::engine::dim4

#include <esve/engine/dim4/Make_Frame.template.cxx>

#endif

