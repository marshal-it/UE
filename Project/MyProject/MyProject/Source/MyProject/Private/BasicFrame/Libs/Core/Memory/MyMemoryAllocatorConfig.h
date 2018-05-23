#pragma once

#if OGRE_DEBUG_MODE

/// Allocate a block of raw memory, and indicate the category of usage
#   define OGRE_MALLOC(bytes, category) ::Ogre::CategorisedAllocPolicy<category>::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
/// Allocate a block of memory for a primitive type, and indicate the category of usage
#   define OGRE_ALLOC_T(T, count, category) static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
/// Free the memory allocated with OGRE_MALLOC or OGRE_ALLOC_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE(ptr, category) ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr)

/// Allocate space for one primitive type, external type or non-virtual type with constructor parameters
#   define OGRE_NEW_T(T, category) new (::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
/// Allocate a block of memory for 'count' primitive types - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
/// Free the memory allocated with OGRE_NEW_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}
/// Free the memory allocated with OGRE_NEW_ARRAY_T. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}

// aligned allocation
/// Allocate a block of raw memory aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_MALLOC_SIMD(bytes, category) ::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
/// Allocate a block of raw memory aligned to user defined boundaries, and indicate the category of usage
#   define OGRE_MALLOC_ALIGN(bytes, category, align) ::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
/// Allocate a block of memory for a primitive type aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_ALLOC_T_SIMD(T, count, category) static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
/// Allocate a block of memory for a primitive type aligned to user defined boundaries, and indicate the category of usage
#   define OGRE_ALLOC_T_ALIGN(T, count, category, align) static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
/// Free the memory allocated with either OGRE_MALLOC_SIMD or OGRE_ALLOC_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_SIMD(ptr, category) ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes(ptr)
/// Free the memory allocated with either OGRE_MALLOC_ALIGN or OGRE_ALLOC_T_ALIGN. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_ALIGN(ptr, category, align) ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes(ptr)

/// Allocate space for one primitive type, external type or non-virtual type aligned to SIMD boundaries
#   define OGRE_NEW_T_SIMD(T, category) new (::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
/// Allocate a block of memory for 'count' primitive types aligned to SIMD boundaries - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T_SIMD(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
/// Free the memory allocated with OGRE_NEW_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T_SIMD(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes(ptr);}
/// Free the memory allocated with OGRE_NEW_ARRAY_T_SIMD. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T_SIMD(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes(ptr);}
/// Allocate space for one primitive type, external type or non-virtual type aligned to user defined boundaries
#   define OGRE_NEW_T_ALIGN(T, category, align) new (::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
/// Allocate a block of memory for 'count' primitive types aligned to user defined boundaries - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T_ALIGN(T, count, category, align) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
/// Free the memory allocated with OGRE_NEW_T_ALIGN. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T_ALIGN(ptr, T, category, align) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes(ptr);}
/// Free the memory allocated with OGRE_NEW_ARRAY_T_ALIGN. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T_ALIGN(ptr, T, count, category, align) if(ptr){for (size_t _b = 0; _b < count; ++_b) { (ptr)[_b].~T();} ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes(ptr);}

// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
// Also hooks up the file/line/function params
// Can only be used with classes that derive from AllocatedObject since customised new/delete needed
#   define OGRE_NEW new (__FILE__, __LINE__, __FUNCTION__)
#   define OGRE_DELETE delete


#else // !OGRE_DEBUG_MODE

/// Allocate a block of raw memory, and indicate the category of usage
#   define OGRE_MALLOC(bytes, category) ::Ogre::CategorisedAllocPolicy<category>::allocateBytes(bytes)
/// Allocate a block of memory for a primitive type, and indicate the category of usage
#   define OGRE_ALLOC_T(T, count, category) static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count)))
/// Free the memory allocated with OGRE_MALLOC or OGRE_ALLOC_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE(ptr, category) ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr)

/// Allocate space for one primitive type, external type or non-virtual type with constructor parameters
#   define OGRE_NEW_T(T, category) new (::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T))) T
/// Allocate a block of memory for 'count' primitive types - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count))), count) 
/// Free the memory allocated with OGRE_NEW_T. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}
/// Free the memory allocated with OGRE_NEW_ARRAY_T. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}

// aligned allocation
/// Allocate a block of raw memory aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_MALLOC_SIMD(bytes, category) ::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(bytes)
/// Allocate a block of raw memory aligned to user defined boundaries, and indicate the category of usage
#   define OGRE_MALLOC_ALIGN(bytes, category, align) ::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(bytes)
/// Allocate a block of memory for a primitive type aligned to SIMD boundaries, and indicate the category of usage
#   define OGRE_ALLOC_T_SIMD(T, count, category) static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T)*(count)))
/// Allocate a block of memory for a primitive type aligned to user defined boundaries, and indicate the category of usage
#   define OGRE_ALLOC_T_ALIGN(T, count, category, align) static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T)*(count)))
/// Free the memory allocated with either OGRE_MALLOC_SIMD or OGRE_ALLOC_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_SIMD(ptr, category) ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes((void*)ptr)
/// Free the memory allocated with either OGRE_MALLOC_ALIGN or OGRE_ALLOC_T_ALIGN. Category is required to be restated to ensure the matching policy is used
#   define OGRE_FREE_ALIGN(ptr, category, align) ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes((void*)ptr)

/// Allocate space for one primitive type, external type or non-virtual type aligned to SIMD boundaries
#   define OGRE_NEW_T_SIMD(T, category) new (::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T))) T
/// Allocate a block of memory for 'count' primitive types aligned to SIMD boundaries - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T_SIMD(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category>::allocateBytes(sizeof(T)*(count))), count) 
/// Free the memory allocated with OGRE_NEW_T_SIMD. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T_SIMD(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes((void*)ptr);}
/// Free the memory allocated with OGRE_NEW_ARRAY_T_SIMD. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T_SIMD(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAlignAllocPolicy<category>::deallocateBytes((void*)ptr);}
/// Allocate space for one primitive type, external type or non-virtual type aligned to user defined boundaries
#   define OGRE_NEW_T_ALIGN(T, category, align) new (::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T))) T
/// Allocate a block of memory for 'count' primitive types aligned to user defined boundaries - do not use for classes that inherit from AllocatedObject
#   define OGRE_NEW_ARRAY_T_ALIGN(T, count, category, align) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAlignAllocPolicy<category, align>::allocateBytes(sizeof(T)*(count))), count) 
/// Free the memory allocated with OGRE_NEW_T_ALIGN. Category is required to be restated to ensure the matching policy is used
#   define OGRE_DELETE_T_ALIGN(ptr, T, category, align) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes((void*)ptr);}
/// Free the memory allocated with OGRE_NEW_ARRAY_T_ALIGN. Category is required to be restated to ensure the matching policy is used, count and type to call destructor
#   define OGRE_DELETE_ARRAY_T_ALIGN(ptr, T, count, category, align) if(ptr){for (size_t _b = 0; _b < count; ++_b) { (ptr)[_b].~T();} ::Ogre::CategorisedAlignAllocPolicy<category, align>::deallocateBytes((void*)ptr);}

// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
#   define OGRE_NEW new 
#   define OGRE_DELETE delete