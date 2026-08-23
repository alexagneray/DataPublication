#ifndef VALUE_H
#define VALUE_H

#define DATA_VARIANT_MAX_SZ  512

#include <stddef.h>
#include <stdint.h>

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
 * \brief Data allocation functions.
 * \addtogroup libdata_alloc
 * @{
 */
data_value_t *alloc_data_from_u8(uint8_t v);
data_value_t *alloc_data_from_s8(int8_t v);
data_value_t *alloc_data_from_u16(int16_t v);
data_value_t *alloc_data_from_s16(uint16_t v);
data_value_t *alloc_data_from_u32(uint32_t v);
data_value_t *alloc_data_from_s32(int32_t v);
data_value_t *alloc_data_from_u64(uint64_t v);
data_value_t *alloc_data_from_s64(int64_t v);
data_value_t *alloc_data_from_f32(float v);
data_value_t *alloc_data_from_f64(double v);
/**
 * @}
 */


#endif // #define VALUE_H