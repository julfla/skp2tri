// Copyright 2013 Trimble Navigation Ltd.  All Rights Reserved
#ifndef SLAPI_MODEL_IMAGE_H_
#define SLAPI_MODEL_IMAGE_H_

#include <slapi/unicodestring.h>
#include <slapi/transformation.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUImageRef
@brief References an image object.
*/

/**
@brief Converts from an \ref SUImageRef to an \ref SUEntityRef.
       This is essentially an upcast operation.
@param[in] image The given image reference.
@return
- The converted \ref SUEntityRef if image is a valid image.
- If not, the returned reference will be invalid.
*/
SU_EXPORT SUEntityRef SUImageToEntity(SUImageRef image);

/**
@brief Converts from an \ref SUEntityRef to an \ref SUImageRef.
       This is essentially a downcast operation so the given entity must be
       convertible to an \ref SUImageRef.
@param[in] entity The given entity reference.
@return
- The converted \ref SUImageRef if the downcast operation succeeds. If not, the
returned reference will be invalid
*/
SU_EXPORT SUImageRef SUImageFromEntity(SUEntityRef entity);

/**
@brief Converts from an \ref SUImageRef to an \ref SUDrawingElementRef.
       This is essentially an upcast operation.
@param[in] image The given image reference.
@return
- The converted \ref SUEntityRef if image is a valid image
- If not, the returned reference will be invalid
*/
SU_EXPORT SUDrawingElementRef SUImageToDrawingElement(SUImageRef image);

/**
@brief Converts from an \ref SUDrawingElementRef to an \ref SUImageRef.
       This is essentially a downcast operation so the given element must be
       convertible to an \ref SUImageRef.
@param[in] drawing_elem The given element reference.
@return
- The converted \ref SUImageRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SUImageRef SUImageFromDrawingElement(SUDrawingElementRef
                                               drawing_elem);

/**
@brief Creates a new image object from an image file specified by a path.
       The created image must be subsequently added to the Entities of a model,
       component definition or a group.
@param[out] image The image object created.
@param file_path  The file path of the source image file.
                  Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if file_path is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if image is NULL
- \ref SU_ERROR_OVERWRITE_VALID if image already references a valid object.
*/
SU_RESULT SUImageCreateFromFile(SUImageRef* image, const char* file_path);

/**
@brief Retrieves the name of an image object.
@param[in]  image The image object.
@param[out] name  The name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if name does not reference a valid object
*/
SU_RESULT SUImageGetName(SUImageRef image, SUStringRef* name);

/**
@brief Sets the name of an image object.
@param[in] image The image object.
@param[in] name  The name to set. Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
*/
SU_RESULT SUImageSetName(SUImageRef image, const char* name);

/**
@brief Retrieves the 3-dimensional homogeneous transform of an image object.
@param[in]  image     The image object.
@param[out] transform The transform retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if transform is NULL
*/
SU_RESULT SUImageGetTransform(SUImageRef image,
                              struct SUTransformation* transform);

/**
@brief Sets the 3-dimensional homogeneous transform of an image object.
@param[in] image     The image object.
@param[in] transform The affine transform to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if transform is NULL
*/
SU_RESULT SUImageSetTransform(SUImageRef image,
                              const struct SUTransformation* transform);

/**
@brief Retrieves the image file name of an image object.
@param[in]  image     The image object.
@param[out] file_name The image file name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if file_name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if file_name does not reference a valid object.
*/
SU_RESULT SUImageGetFileName(SUImageRef image, SUStringRef* file_name);

/**
@brief Retrieves the world dimensions of an image object.
@param[in]  image  The image object.
@param[out] width  The width dimension retrieved.
@param[out] height The height dimension retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if width or height is NULL
*/
SU_RESULT SUImageGetDimensions(SUImageRef image, double* width, double* height);

/**
@brief Retrieves the width and height dimensions of an image object in pixels.
@param[in]  image  The image object.
@param[out] width  The width dimension retrieved.
@param[out] height The height dimension retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if width or height is NULL
*/
SU_RESULT SUImageGetPixelDimensions(SUImageRef image, size_t* width,
                                    size_t* height);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SLAPI_MODEL_IMAGE_H_
