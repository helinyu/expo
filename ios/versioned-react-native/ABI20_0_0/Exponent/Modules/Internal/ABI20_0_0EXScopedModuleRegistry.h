// Copyright 2015-present 650 Industries. All rights reserved.

#import <ReactABI20_0_0/ABI20_0_0RCTBridge.h>
#import <ReactABI20_0_0/ABI20_0_0RCTBridgeModule.h>

#import "ABI20_0_0EXScopedBridgeModule.h"

/**
 *  Use this in place of ABI20_0_0RCT_EXPORT_MODULE() to auto-init an instance of your scoped module on ABI20_0_0RCTBridge instances.
 *  @param js_name same as ABI20_0_0RCT_EXPORT_MODULE(), the module name available in JS
 *  @param kernel_service_class if specified, your module will be passed an unversioned instance of this kernel service at runtime.
 *         e.g. MyKernelService -> an instance of ABI20_0_0EXMyKernelService
 */
#define ABI20_0_0EX_EXPORT_SCOPED_MODULE(js_name, kernel_service_class) \
ABI20_0_0RCT_EXTERN void ABI20_0_0EXRegisterScopedModule(Class, NSString *); \
+ (NSString *)moduleName { return @#js_name; } \
+ (void)load { ABI20_0_0EXRegisterScopedModule(self, @#kernel_service_class); }

/**
 *  Provides a namespace/bottleneck through which scoped modules
 *  can make themselves accessible to other modules.
 *
 *  e.g. ABI20_0_0EX_DECLARE_SCOPED_MODULE_GETTER(ABI20_0_0EXCoolClass, coolClass)
 *  provides the getter `_bridge.scopedModules.coolClass`.
 */
#define ABI20_0_0EX_DECLARE_SCOPED_MODULE_GETTER(className, getter) \
@interface ABI20_0_0EXScopedModuleRegistry (className) \
@property (nonatomic, readonly) className *getter; \
@end\

/**
 *  Use in conjunction with ABI20_0_0EX_DECLARE_SCOPED_MODULE_GETTER, but in the corresponding implementation file.
 */
#define ABI20_0_0EX_DEFINE_SCOPED_MODULE_GETTER(className, getter) \
@implementation  ABI20_0_0EXScopedModuleRegistry (className) \
- (className *)getter { return [self.bridge moduleForClass:[className class]]; } \
@end\

@interface ABI20_0_0EXScopedModuleRegistry : NSObject <ABI20_0_0RCTBridgeModule>

@end

@interface ABI20_0_0RCTBridge (ABI20_0_0EXScopedModuleRegistry)

@property (nonatomic, readonly) ABI20_0_0EXScopedModuleRegistry *scopedModules;

@end
