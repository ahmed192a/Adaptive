#ifndef ARA_SM_COMMON_TYPES_H
#define ARA_SM_COMMON_TYPES_H

#include <string>
#include <vector>


namespace ara {
    namespace sm {

            /** Type definitions **/

            // [SWS_SM_91019]
            /*
             * Name        : FunctionGroupNameType
             * Kind        : STRING
             * Description : full qualified FunctionGroup shortName.
             */
            using FunctionGroupNameType = std::string;


            // [SWS_SM_91018]
            /*
             * Name        : FunctionGroupListType
             * Kind        : VECTOR
             * Subelements : FunctionGroupNameType
             * Description : A list of FunctionGroups.
             */
            using FunctionGroupListType = std::vector<FunctionGroupNameType>;


    } // namespace sm
} // namespace ara

#endif // ARA_SM_COMMON_TYPES_H
