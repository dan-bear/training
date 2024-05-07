///https://softwareengineering.stackexchange.com/questions/162643/
/// 1: Most of the times they are not needed, in this case,
///    it's better to use a private member.
///    YAGNI - you arent gonna need it.
/// 2: They tend to lead to LSP issues - Liskov substitution principle
///    Protected variables generally have some intrinsic invariance
///    associated with them (or else they would be public). Inheritors
///    then need to maintain those properties, which people can screw up
///    or willfully violate.
/// 3: They tend to violate OCP - open-close-principle open to extension
///                               but close to modification.
///    If the base class makes too many assumptions about the protected
///    member, or the inheritor is too flexible with the behavior of the
///    class, it can lead to the base class' behavior being modified by
///    that extension.
/// 4: They tend to lead to inheritance for extension rather than composition.
///    This tends to lead to tighter coupling, more violations of SRP (single
///    responsibility priciple), more difficult testing, and a slew of other
///    things that fall within the 'favor composition over inheritance' discussion. x 
