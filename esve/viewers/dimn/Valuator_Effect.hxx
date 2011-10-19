
#ifndef esve_viewers_dimn_Valuator_Effect_hxx
#define esve_viewers_dimn_Valuator_Effect_hxx

namespace esve { namespace viewers { namespace dimn {

namespace valuator_effect {

enum Valuator_Effect
{
    CHANGES_DOMAIN,
    CHANGES_DOMAIN_CLIP,
    CHANGES_SURFACE,
    CHANGES_SURFACE_CLIP,
    CHANGES_COLOR
} ;

} // namespace valuator_effect

typedef valuator_effect::Valuator_Effect Valuator_Effect ;

}}} // namespace esve::viewers::dimn

#endif
