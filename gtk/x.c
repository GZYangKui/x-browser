#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.x"), aligned (8)))
#else
# define SECTION
#endif

#ifdef _MSC_VER
static const SECTION union { const guint8 data[629]; const double alignment; void * const ptr;}  x_resource_data = { {
  0107, 0126, 0141, 0162, 0151, 0141, 0156, 0164, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 
  0030, 0000, 0000, 0000, 0164, 0000, 0000, 0000, 0000, 0000, 0000, 0050, 0003, 0000, 0000, 0000, 
  0000, 0000, 0000, 0000, 0002, 0000, 0000, 0000, 0002, 0000, 0000, 0000, 0035, 0345, 0127, 0272, 
  0002, 0000, 0000, 0000, 0164, 0000, 0000, 0000, 0014, 0000, 0166, 0000, 0200, 0000, 0000, 0000, 
  0375, 0000, 0000, 0000, 0057, 0045, 0070, 0364, 0002, 0000, 0000, 0000, 0375, 0000, 0000, 0000, 
  0014, 0000, 0166, 0000, 0020, 0001, 0000, 0000, 0150, 0002, 0000, 0000, 0324, 0265, 0002, 0000, 
  0377, 0377, 0377, 0377, 0150, 0002, 0000, 0000, 0001, 0000, 0114, 0000, 0154, 0002, 0000, 0000, 
  0164, 0002, 0000, 0000, 0153, 0167, 0137, 0163, 0164, 0171, 0154, 0145, 0056, 0143, 0163, 0163, 
  0155, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0147, 0162, 0151, 0144, 0040, 0173, 0012, 0040, 
  0040, 0040, 0040, 0142, 0141, 0143, 0153, 0147, 0162, 0157, 0165, 0156, 0144, 0055, 0143, 0157, 
  0154, 0157, 0162, 0072, 0040, 0043, 0071, 0143, 0071, 0143, 0145, 0065, 0073, 0012, 0040, 0040, 
  0040, 0040, 0146, 0157, 0156, 0164, 0055, 0163, 0151, 0172, 0145, 0072, 0040, 0061, 0145, 0155, 
  0073, 0012, 0175, 0012, 0012, 0147, 0162, 0151, 0144, 0040, 0076, 0040, 0142, 0165, 0164, 0164, 
  0157, 0156, 0040, 0173, 0012, 0040, 0040, 0040, 0040, 0142, 0141, 0143, 0153, 0147, 0162, 0157, 
  0165, 0156, 0144, 0055, 0143, 0157, 0154, 0157, 0162, 0072, 0040, 0043, 0071, 0143, 0071, 0143, 
  0145, 0065, 0073, 0012, 0175, 0000, 0000, 0050, 0165, 0165, 0141, 0171, 0051, 0153, 0167, 0137, 
  0143, 0154, 0145, 0141, 0162, 0056, 0160, 0156, 0147, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 
  0110, 0001, 0000, 0000, 0000, 0000, 0000, 0000, 0211, 0120, 0116, 0107, 0015, 0012, 0032, 0012, 
  0000, 0000, 0000, 0015, 0111, 0110, 0104, 0122, 0000, 0000, 0000, 0017, 0000, 0000, 0000, 0017, 
  0010, 0006, 0000, 0000, 0000, 0073, 0326, 0225, 0112, 0000, 0000, 0001, 0017, 0111, 0104, 0101, 
  0124, 0070, 0117, 0245, 0223, 0061, 0112, 0104, 0061, 0020, 0206, 0377, 0231, 0023, 0350, 0065, 
  0234, 0004, 0366, 0020, 0172, 0010, 0025, 0331, 0003, 0330, 0013, 0332, 0155, 0343, 0026, 0026, 
  0212, 0154, 0041, 0202, 0235, 0132, 0150, 0055, 0132, 0050, 0172, 0004, 0315, 0044, 0027, 0260, 
  0261, 0260, 0260, 0262, 0315, 0110, 0140, 0337, 0022, 0175, 0217, 0345, 0311, 0113, 0067, 0114, 
  0276, 0231, 0377, 0317, 0114, 0010, 0003, 0016, 0015, 0140, 0321, 0011, 0213, 0310, 0230, 0210, 
  0126, 0346, 0205, 0337, 0352, 0006, 0146, 0066, 0052, 0161, 0112, 0351, 0244, 0005, 0213, 0310, 
  0032, 0063, 0337, 0001, 0370, 0066, 0263, 0317, 0016, 0145, 0043, 0063, 0233, 0264, 0340, 0071, 
  0170, 0003, 0140, 0242, 0252, 0267, 0135, 0226, 0234, 0163, 0317, 0045, 0037, 0143, 0174, 0131, 
  0164, 0376, 0013, 0072, 0347, 0166, 0210, 0350, 0103, 0125, 0037, 0105, 0144, 0023, 0300, 0127, 
  0112, 0351, 0241, 0005, 0127, 0340, 0124, 0125, 0257, 0112, 0107, 0357, 0375, 0266, 0231, 0135, 
  0002, 0070, 0004, 0160, 0100, 0104, 0033, 0245, 0320, 0057, 0270, 0002, 0117, 0125, 0365, 0274, 
  0226, 0052, 0042, 0063, 0042, 0332, 0145, 0346, 0275, 0020, 0302, 0121, 0311, 0055, 0353, 0274, 
  0050, 0120, 0244, 0022, 0321, 0065, 0063, 0117, 0163, 0316, 0373, 0314, 0274, 0036, 0102, 0170, 
  0132, 0352, 0331, 0314, 0146, 0061, 0306, 0263, 0332, 0263, 0367, 0176, 0253, 0170, 0126, 0325, 
  0373, 0116, 0270, 0110, 0152, 0054, 0344, 0234, 0057, 0122, 0112, 0307, 0275, 0137, 0273, 0271, 
  0330, 0314, 0331, 0314, 0062, 0200, 0367, 0336, 0163, 0256, 0012, 0214, 0001, 0254, 0226, 0230, 
  0210, 0136, 0173, 0157, 0330, 0177, 0166, 0175, 0320, 0307, 0370, 0001, 0003, 0350, 0241, 0020, 
  0156, 0060, 0237, 0026, 0000, 0000, 0000, 0000, 0111, 0105, 0116, 0104, 0256, 0102, 0140, 0202, 
  0000, 0000, 0050, 0165, 0165, 0141, 0171, 0051, 0057, 0000, 0000, 0000, 0001, 0000, 0000, 0000, 
  0000, 0000, 0000, 0000
} };
#else /* _MSC_VER */
static const SECTION union { const guint8 data[629]; const double alignment; void * const ptr;}  x_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\164\000\000\000\000\000\000\050\003\000\000\000"
  "\000\000\000\000\002\000\000\000\002\000\000\000\035\345\127\272"
  "\002\000\000\000\164\000\000\000\014\000\166\000\200\000\000\000"
  "\375\000\000\000\057\045\070\364\002\000\000\000\375\000\000\000"
  "\014\000\166\000\020\001\000\000\150\002\000\000\324\265\002\000"
  "\377\377\377\377\150\002\000\000\001\000\114\000\154\002\000\000"
  "\164\002\000\000\153\167\137\163\164\171\154\145\056\143\163\163"
  "\155\000\000\000\000\000\000\000\147\162\151\144\040\173\012\040"
  "\040\040\040\142\141\143\153\147\162\157\165\156\144\055\143\157"
  "\154\157\162\072\040\043\071\143\071\143\145\065\073\012\040\040"
  "\040\040\146\157\156\164\055\163\151\172\145\072\040\061\145\155"
  "\073\012\175\012\012\147\162\151\144\040\076\040\142\165\164\164"
  "\157\156\040\173\012\040\040\040\040\142\141\143\153\147\162\157"
  "\165\156\144\055\143\157\154\157\162\072\040\043\071\143\071\143"
  "\145\065\073\012\175\000\000\050\165\165\141\171\051\153\167\137"
  "\143\154\145\141\162\056\160\156\147\000\000\000\000\000\000\000"
  "\110\001\000\000\000\000\000\000\211\120\116\107\015\012\032\012"
  "\000\000\000\015\111\110\104\122\000\000\000\017\000\000\000\017"
  "\010\006\000\000\000\073\326\225\112\000\000\001\017\111\104\101"
  "\124\070\117\245\223\061\112\104\061\020\206\377\231\023\350\065"
  "\234\004\366\020\172\010\025\331\003\330\013\332\155\343\026\026"
  "\212\154\041\202\235\132\150\055\132\050\172\004\315\044\027\260"
  "\261\260\260\262\315\110\140\337\022\175\217\345\311\113\067\114"
  "\276\231\377\317\114\010\003\016\015\140\321\011\213\310\230\210"
  "\126\346\205\337\352\006\146\066\052\161\112\351\244\005\213\310"
  "\032\063\337\001\370\066\263\317\016\145\043\063\233\264\340\071"
  "\170\003\140\242\252\267\135\226\234\163\317\045\037\143\174\131"
  "\164\376\013\072\347\166\210\350\103\125\037\105\144\023\300\127"
  "\112\351\241\005\127\340\124\125\257\112\107\357\375\266\231\135"
  "\002\070\004\160\100\104\033\245\320\057\270\002\117\125\365\274"
  "\226\052\042\063\042\332\145\346\275\020\302\121\311\055\353\274"
  "\050\120\244\022\321\065\063\117\163\316\373\314\274\036\102\170"
  "\132\352\331\314\146\061\306\263\332\263\367\176\253\170\126\325"
  "\373\116\270\110\152\054\344\234\057\122\112\307\275\137\273\271"
  "\330\314\331\314\062\200\367\336\163\256\012\214\001\254\226\230"
  "\210\136\173\157\330\177\166\175\320\307\370\001\003\350\241\020"
  "\156\060\237\026\000\000\000\000\111\105\116\104\256\102\140\202"
  "\000\000\050\165\165\141\171\051\057\000\000\000\001\000\000\000"
  "\000\000\000\000" };
#endif /* !_MSC_VER */

static GStaticResource static_resource = { x_resource_data.data, sizeof (x_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *x_get_resource (void);
GResource *x_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
