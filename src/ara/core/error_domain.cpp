
// #include "error_domain.h"

// namespace ara
// {
// 	namespace core
// 	{
// 		// SWS_CORE_00135
// 		/**
// 		 * \brief Construct a new instance with the given identifier.
// 		 *
// 		 * Identifiers are expected to be system-wide unique.
// 		 *
// 		 */

// 		constexpr ErrorDomain::ErrorDomain (IdType id) noexcept : idType(id)
// 		{

// 		}


//         // SWS_CORE_00151
//         /**
//          * \brief Return the unique domain identifier.
//          *
//          * \return constexpr IdType     the identifier
//          */

// 		// constexpr ErrorDomain::IdType ErrorDomain::Id() const noexcept
// 		// {
// 		// 	return this->idType;
// 		// }


//         // SWS_CORE_00137
//         /**
//          * \brief Compare for equality with another ErrorDomain instance.
//          *
//          * Two ErrorDomain instances compare equal when their identifiers (returned by Id()) are equal.
//          *
//          * \param[in] other     the other instance
//          *
//          * \return true         if other is equal to *this
//          * \return false        otherwise
//          */
//         // constexpr bool ErrorDomain::operator==(ErrorDomain const &other) const noexcept
//         // {
//         // 	return ( this->ErrorDomain::Id() == other.ErrorDomain::Id() ) ? true : false;
//         // }


//         // SWS_CORE_00138
//         /**
//          * \brief Compare for non-equality with another ErrorDomain instance.
//          *
//          * \param[in] other     the other instance
//          *
//          * \return true         if other is not equal to *this
//          * \return false        otherwise
//          */
//         // constexpr bool ErrorDomain::operator!=(ErrorDomain const &other) const noexcept
//         // {
//         // 	return ( this->ErrorDomain::Id() == other.ErrorDomain::Id() ) ? false : true;
//         // }

// 	}
// }
