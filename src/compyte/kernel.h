#ifndef COMPYTE_KERNEL_H
#define COMPYTE_KERNEL_H
/** \file kernel.h
 *  \brief Kernel functions.
 */

#include <compyte/buffer.h>
#include <compyte/array.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef CONFUSE_EMACS
}
#endif

/**
 * Kernel information structure.
 */
typedef struct _GpuKernel {
  /**
   * Device kernel reference.
   */
  gpukernel *k;
  /**
   * Backend operations vector.
   */
  const compyte_buffer_ops *ops;
} GpuKernel;

/**
 * Initialize a kernel structure.
 *
 * `lens` holds the size of each source string.  If is it NULL or an
 * element has a value of 0 the length will be determined using strlen()
 * or equivalent code.
 *
 * \param k a kernel structure
 * \param ops operations vector
 * \param ctx context in which to build the kernel
 * \param count number of source code strings
 * \param strs C array of source code strings
 * \param lens C array with the size of each string or NULL
 * \param name name of the kernel function
 * \param flags kernel use flags (see \ref ga_usefl)
 *
 * \return GA_NO_ERROR if the operation is successful
 * \return any other value if an error occured
 */
COMPYTE_PUBLIC int GpuKernel_init(GpuKernel *k, const compyte_buffer_ops *ops,
                                  void *ctx, unsigned int count,
                                  const char **strs, size_t *lens,
                                  const char *name, int flags);

/**
 * Clear and release data associated with a kernel.
 *
 * \param k the kernel to release
 */
COMPYTE_PUBLIC void GpuKernel_clear(GpuKernel *k);

/**
 * Returns the context in which a kernel was built.
 *
 * \param k a kernel
 *
 * \returns a context pointer
 */
COMPYTE_PUBLIC void *GpuKernel_context(GpuKernel *k);

/**
 * Set a scalar argument for a kernel.
 *
 * \param k a kernel
 * \param index argument index to set
 * \param typecode type of the argument to set
 * \param arg pointer to the scalar value
 *
 * \return GA_NO_ERROR if the operation is successful
 * \return any other value if an error occured
 */
COMPYTE_PUBLIC int GpuKernel_setarg(GpuKernel *k, unsigned int index,
                                    int typecode, void *arg);
/**
 * Set an array argument for a kernel.
 *
 * \param k a kernel
 * \param index argument index to set
 * \param a array argument
 *
 * \return GA_NO_ERROR if the operation is successful
 * \return any other value if an error occured
 */
COMPYTE_PUBLIC int GpuKernel_setbufarg(GpuKernel *k, unsigned int index,
                                       GpuArray *a);

/**
 * Launch the execution of a kernel.
 *
 * You either specify the block and grid sizes (`ls` and `gs`) or the
 * total size (`n`). Set a value to `0` to indicate it is
 * unspecified. You can also specify the total size (`n`) and one of
 * the block (`ls`) or grid (`gs`) size.
 *
 * If you leave one or both of `ls` or `gs`, it will be filled
 * according to a heuristic to get a good performance out of your
 * hardware. However the number of kernel instances that will be run
 * can be slightly higher than the total size you specified in order
 * to avoid performance degradation. Your kernel should be ready to
 * handle this.
 *
 * \param k the kernel to launch
 * \param n number of instances to launch
 * \param ls size of launch blocks
 * \param gs size of launch grid
 */
COMPYTE_PUBLIC int GpuKernel_call2(GpuKernel *k, size_t n[2],
                                  size_t ls[2], size_t gs[2]);

COMPYTE_PUBLIC int GpuKernel_call(GpuKernel *k, size_t n,
                                  size_t ls, size_t gs);

#ifdef __cplusplus
}
#endif

#endif
