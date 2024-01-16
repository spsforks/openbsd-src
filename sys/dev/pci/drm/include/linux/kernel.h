/* Public domain. */

#ifndef _LINUX_KERNEL_H
#define _LINUX_KERNEL_H

#include <sys/stdint.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/stdarg.h>
#include <sys/malloc.h>

#include <linux/types.h>
#include <linux/compiler.h>
#include <linux/bitops.h>
#include <linux/log2.h>
#include <linux/linkage.h>
#include <linux/printk.h>
#include <linux/typecheck.h>
#include <linux/container_of.h>
#include <linux/stddef.h>
#include <linux/align.h>
#include <asm/byteorder.h>

#define swap(a, b) \
	do { __typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while(0)

#define offsetofend(s, e) (offsetof(s, e) + sizeof((((s *)0)->e)))

#define S8_MAX		INT8_MAX
#define S16_MAX		INT16_MAX
#define S32_MAX		INT32_MAX
#define S64_MAX		INT64_MAX

#define U8_MAX		UINT8_MAX
#define U16_MAX		UINT16_MAX
#define U32_MAX		UINT32_MAX
#define U64_C(x)	UINT64_C(x)
#define U64_MAX		UINT64_MAX

#define ARRAY_SIZE nitems

#define lower_32_bits(n)	((u32)(n))
#define upper_32_bits(_val)	((u32)(((_val) >> 16) >> 16))

#define scnprintf(str, size, fmt, arg...) snprintf(str, size, fmt, ## arg)

#define min_t(t, a, b) ({ \
	t __min_a = (a); \
	t __min_b = (b); \
	__min_a < __min_b ? __min_a : __min_b; })

#define max_t(t, a, b) ({ \
	t __max_a = (a); \
	t __max_b = (b); \
	__max_a > __max_b ? __max_a : __max_b; })

#define clamp_t(t, x, a, b) min_t(t, max_t(t, x, a), b)
#define clamp(x, a, b) clamp_t(__typeof(x), x, a, b)
#define clamp_val(x, a, b) clamp_t(__typeof(x), x, a, b)

#define min(a, b) MIN(a, b)
#define max(a, b) MAX(a, b)
#define min3(x, y, z) MIN(x, MIN(y, z))
#define max3(x, y, z) MAX(x, MAX(y, z))

#define min_not_zero(a, b) (a == 0) ? b : ((b == 0) ? a : min(a, b))

#define mult_frac(x, n, d) (((x) * (n)) / (d))

#define roundup2(x, y) (((x) + ((y) - 1)) & (~((__typeof(x))(y) - 1)))
#define rounddown2(x, y) ((x) & ~((__typeof(x))(y) - 1))
#define round_up(x, y) ((((x) + ((y) - 1)) / (y)) * (y))
#define round_down(x, y) (((x) / (y)) * (y)) /* y is power of two */
#define rounddown(x, y) (((x) / (y)) * (y)) /* arbitrary y */
#define DIV_ROUND_UP(x, y)	(((x) + ((y) - 1)) / (y))
#define DIV_ROUND_UP_ULL(x, y)	DIV_ROUND_UP(x, y)
#define DIV_ROUND_DOWN(x, y)	((x) / (y))
#define DIV_ROUND_DOWN_ULL(x, y)	DIV_ROUND_DOWN(x, y)
#define DIV_ROUND_CLOSEST(x, y)	(((x) + ((y) / 2)) / (y))
#define DIV_ROUND_CLOSEST_ULL(x, y)	DIV_ROUND_CLOSEST(x, y)

#define IS_ALIGNED(x, y)	(((x) & ((y) - 1)) == 0)
#define PTR_ALIGN(x, y)		((__typeof(x))roundup2((unsigned long)(x), (y)))
#define ALIGN_DOWN(x, y)	((__typeof(x))rounddown2((unsigned long)(x), (y)))

static inline char *
kvasprintf(int flags, const char *fmt, va_list ap)
{
	char *buf;
	size_t len;
	va_list vl;

	va_copy(vl, ap);
	len = vsnprintf(NULL, 0, fmt, vl);
	va_end(vl);

	buf = malloc(len + 1, M_DRM, flags);
	if (buf) {
		vsnprintf(buf, len + 1, fmt, ap);
	}

	return buf;
}

static inline char *
kasprintf(int flags, const char *fmt, ...)
{
	char *buf;
	va_list ap;

	va_start(ap, fmt);
	buf = kvasprintf(flags, fmt, ap);
	va_end(ap);

	return buf;
}

static inline int
vscnprintf(char *buf, size_t size, const char *fmt, va_list ap)
{
	int nc;

	nc = vsnprintf(buf, size, fmt, ap);
	if (nc > (size - 1))
		return (size - 1);
	else
		return nc;
}

static inline int
_in_dbg_master(void)
{
#ifdef DDB
	return (db_active);
#endif
	return (0);
}

#define oops_in_progress _in_dbg_master()

#define might_sleep()		assertwaitok()
#define might_sleep_if(x)	do {	\
	if (x)				\
		assertwaitok();		\
} while (0)

#define add_taint(x, y)
#define TAINT_MACHINE_CHECK	0
#define TAINT_WARN		1
#define LOCKDEP_STILL_OK	0

#define u64_to_user_ptr(x)	((void *)(uintptr_t)(x))

#define _RET_IP_		__builtin_return_address(0)

#define STUB() do { printf("%s: stub\n", __func__); } while(0)

#define CONCATENATE(x, y)	__CONCAT(x, y)

#define PTR_IF(c, p)		((c) ? (p) : NULL)

#endif
