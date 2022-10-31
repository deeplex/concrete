
============================
 Data defined Status Domain
============================

::

    #include <dplx/cncr/data_defined_status_domain.hpp>
    namespace dplx::cncr {}

.. namespace:: dplx::cncr

This module allows "generating" a ``status_code_domain`` (see the 
`status-code <https://github.com/ned14/status-code>`_ GitHub project) for a
return code enumeration. In order to generate a ``status_code_domain`` one
needs to specialize :texpr:`status_enum_definition` with the enumeration type,
like so:
::

    enum class test_errc
    {
        success = 0,
        perm = 3,
        other_success = 5,
        not_implemented = 7,
    };

    template <>
    struct dplx::cncr::status_enum_definition<test_errc>
        : status_enum_definition_defaults<test_errc>
    {
        static constexpr char domain_id[]
                = "{09E0ECBF-A737-454D-8633-17E733CDE15F}";
        static constexpr char domain_name[] = "test-domain";

        static constexpr value_descriptor values[] = {
                {        code::success,           generic_errc::success,       "yay!"},
                {           code::perm, generic_errc::permission_denied,      "oh no"},
                {  code::other_success,           generic_errc::success,     "oh kay"},
                {code::not_implemented,           generic_errc::unknown, "till later"},
        };
    }

.. concept:: template <typename Enum> \
             status_enum

    **Notation**
    
    .. type:: definition = status_enum_definition<Enum>

        The specialization containing the domain name, id and value
        descriptions.

    **Valid Expressions**

    - :expr:`std::string_view{definition::domain_name}`, the domain name
      specified can be constexpr converted to a :texpr:`string_view`.
    - :expr:`std::string_view{definition::domain_id}`, the domain uuid
      specified can be constexpr converted to a :texpr:`string_view`.
    - :expr:`std::span<status_enum_value_descriptor<Enum> const>{definition::values}`
      the

.. struct:: template <typename Enum> \
            status_enum_value_descriptor

    A data first descriptor tuple which consists of a description and an
    equivalent code for a :texpr:`value`.

    .. member:: Enum value

        The value to be described.

    .. member:: ::system_error2::errc equivalent

        The generic code equivalent to :texpr:`value`. 
        
        The ``::system_error2::errc::success`` and
        ``::system_error2::errc::unknown`` values  indicate that :texpr:`value`
        is not an error or no equivalent generic code exists respectively.

    .. member:: std::string_view description

        A string describing the situation indicated by :texpr:`value`.

.. struct:: template <typename Enum> \
            status_enum_definition_defaults

    A CRTP base class for :texpr:`status_enum_definition` specializiations which
    introduces a few type aliases allowing for terser definitions.

    .. type:: code = Enum

        The enumeration type the status code is generated for.

    .. type:: generic_errc = ::system_error2::errc

        The generic error enumeration from the status-code library.

    .. type:: value_descriptor = status_enum_value_descriptor<Enum>

        The value descriptor type for :texpr:`Enum`.

.. var:: template <status_enum Enum> \
         inline constexpr \
         data_defined_status_domain_type<Enum> data_defined_status_domain

    The default status domain instance for data defined status enumerations.
    There shouldn't be any need to reference it directly.

.. class:: template <status_enum Enum> \
           data_defined_status_domain_type \
           : public SYSTEM_ERROR2_NAMESPACE::status_code_domain

    The domain type template which implements a status domain based on the
    :expr:`status_enum_definition<Enum>`.

    .. seealso::

        The  `base class documentation <https://ned14.github.io/status-code/doc_status_code_domain.html#standardese-system_error2__status_code_domain>`_.

.. struct:: template <status_enum Enum> \
            status_enum_definition

    This template serves as the main customization point. There exists no main
    definition. See the example given at the top for a specialization example.
