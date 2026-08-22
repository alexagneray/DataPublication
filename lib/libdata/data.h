/**
 * \brief Data storage management.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


#define DATA_LABEL_LEN       128
#define DATA_GROUP_LABEL_LEN 128 
#define DATA_VARIANT_MAX_SZ  512



typedef enum data_ret_e
{
    DATA_RET_OK,                   /**< Success. */
    DATA_RET_FAIL,                 /**< The operation failed (generic error) */
    DATA_RET_DATA_ALREADY_EXISTS,  /**< The specified data already exists. */
    DATA_RET_GROUP_ALREADY_EXISTS, /**< The specified group already exists */
    DATA_RET_DATA_NOT_FOUND,       /**< The specified data is not found. */
    DATA_RET_GROUP_NOT_FOUND,      /**< The specified group is not found. */
    DATA_RET_MEM_ERR               /**< Error while allocating memory. (Not enough space)*/
} data_ret_t;


/**
 * Underlying generic type to store data.
 * 
 */
typedef union data_variant_u
{
    char     raw[DATA_VARIANT_MAX_SZ];

    int8_t   s8;
    uint8_t  u8;
    int16_t  s16;
    uint16_t u16;
    int32_t  s32;
    uint32_t u32;
    int64_t  s64;
    uint64_t u64;
    
    float    f32;
    double   f64;   
} data_variant_t;

/**
 * \brief Types of the stored data. 
 */
typedef enum data_type_e
{
    DATA_TYPE_RAW,
    DATA_TYPE_S8,
    DATA_TYPE_U8,
    DATA_TYPE_S16,
    DATA_TYPE_U16,
    DATA_TYPE_S32,
    DATA_TYPE_U32,
    DATA_TYPE_U64,
    DATA_TYPE_S64,
    DATA_TYPE_F32,
    DATA_TYPE_F64
} data_type_t;

/**
 * \brief 
 */
typedef struct data_value_s
{
    data_variant_t var;
    data_type_t    type;
    
} data_value_t;


/**
 * \brief Initialisation / Destruction.
 * \addtogroup libdata_init_destroy
 * @{
 */
/**
 * \brief Initialisation of the data library.
 * 
 * \retval DATA_RET_OK Success.
 * \retval DATA_RET_MEM_ERR Error while allocating memory.
 */
data_ret_t lib_data_init();

/**
 * \brief Destruction of the data library.
 * 
 * \retval DATA_RET_OK Success.
 */
data_ret_t lib_data_destroy();

/**
 * @}
 */




/**
 * \brief Data adding.
 * \addtogroup libdata_add
 * @{
 */

/**
 * \brief Add a new group. 
 * 
 * \param[in] group_label Label of the new group.
 * 
 * \retval DATA_RET_OK Success. 
 * \retval DATA_RET_GROUP_ALREADY_EXISTS A group with this label already exists. 
 * \retval DATA_RET_MEM_ERR Error while allocating memory.
 */
data_ret_t add_group(const char *group_label);

/**
 * \brief Add data to a group. 
 * 
 * \note The caller loses the ownership of the data referenced by var. 
 * 
 * \param[in] group_label Label of the group.
 * \param[in] label Label of the data.
 * \param[in] val Value of the data, the caller loses the ownership of the referenced data.
 * 
 * \retval DATA_RET_OK Success.
 * \retval 
 */
data_ret_t add_data_to_group(char *group_label, const char *label, data_value_t *val);
/**
 * @}
 */


 /**
 * \brief Data deletion
 * \addtogroup libdata_del
 * @{
 */

/**
 * \brief Delete the group with the specified label.
 * 
 * \param[in] group_label Label of the group to delete.
 * 
 * \retval DATA_RET_OK Success.
 * \retval DATA_RET_GROUP_NOT_FOUND The specified group is not found.
 */
data_ret_t del_group(const char *group_label);

/**
 * \brief Delete the data with the specified label. 
 * 
 * \param[in] label Label of the data to delete. 
 * \param[in] group_label Label of the group containing the data to delete. 
 * 
 * \retval DATA_RET_OK Success. 
 * \retval DATA_RET_GROUP_NOT_FOUND The specified group is not found.
 * \retval DATA_RET_DATA_NOT_FOUND The specified data is not found.
 */
data_ret_t del_data(const char *label, const char *group_label);
/**
 * @}
 */

/**
 * \brief Data updating
 * \addtogroup libdata_upd
 * @{
 */

/**
 * \brief Update the name of the group.
 * 
 * \param[in] group_label Label of the group to update. 
 * \param[in] new_group_label New label for the group. 
 * 
 * \retval DATA_RET_OK Success.
 * \retval DATA_RET_GROUP_NOT_FOUND The specified group is not found.
 * \retval DATA_RET_GROUP_ALREADY_EXISTS A group with this label already exists. 
 */

data_ret_t upd_group(const char *group_label, const char *new_group_label);

/**
 * \brief Update the data var of a certain group.
 * 
 * \note The caller loses the ownership of the data referenced by var. 
 * 
 * \param[in] group_label Label of the group.
 * \param[in] label Label of the data.
 * \param[in] val Value of the data, the caller loses the ownership of the referenced data.
 * 
 * \retval DATA_RET_OK Success.
 * \retval DATA_RET_GROUP_NOT_FOUND No data group with the specified group label found.
 * \retval DATA_RET_DATA_NOT_FOUND No data with the specified label found in the group.
 */
data_ret_t upd_data_var(const char *group_label, const char *label, data_value_t *val);

/**
 * \brief Update the data label of a certain group.
 * 
 * 
 * \param[in] group_label Label of the group.
 * \param[in] label Label of the data.
 * \param[in] new_label New label for the data.
 * 
 * \retval DATA_RET_OK Success.
 * \retval DATA_RET_GROUP_NOT_FOUND No data group with the specified group label found.
 * \retval DATA_RET_DATA_NOT_FOUND No data with the specified label found in the group.
 */
data_ret_t upd_data_label(const char *group_label, const char *label, const char *new_label);


/**
 * @}
 */




 /**
  * \brief Get information from the data storage.
  * 
  * \addtogroup libdata_get
  * @{
  */

size_t get_data_group_count();
size_t get_data_count_in_group(const char *group_label);
bool is_init();

/**
 * @}
 */