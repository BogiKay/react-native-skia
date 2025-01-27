#pragma once

#include <memory>
#include <string>

#include <fbjni/fbjni.h>
#include <jni.h>
#include <jsi/jsi.h>

#include <JniSkiaBaseView.h>
#include <JniSkiaManager.h>
#include <RNSkAndroidView.h>
#include <RNSkJsView.h>

#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <fbjni/detail/Hybrid.h>

namespace RNSkia {
namespace jsi = facebook::jsi;
namespace jni = facebook::jni;

class JniSkiaDrawView : public jni::HybridClass<JniSkiaDrawView>,
                        public JniSkiaBaseView {
public:
  static auto constexpr kJavaDescriptor =
      "Lcom/shopify/reactnative/skia/SkiaDrawView;";

  static jni::local_ref<jhybriddata>
  initHybrid(jni::alias_ref<jhybridobject> jThis,
             jni::alias_ref<JniSkiaManager::javaobject> skiaManager) {
    return makeCxxInstance(jThis, skiaManager);
  }

  static void registerNatives() {
    registerHybrid({
        makeNativeMethod("initHybrid", JniSkiaDrawView::initHybrid),
        makeNativeMethod("surfaceAvailable", JniSkiaDrawView::surfaceAvailable),
        makeNativeMethod("surfaceDestroyed", JniSkiaDrawView::surfaceDestroyed),
        makeNativeMethod("surfaceSizeChanged",
                         JniSkiaDrawView::surfaceSizeChanged),
        makeNativeMethod("setMode", JniSkiaDrawView::setMode),
        makeNativeMethod("setDebugMode", JniSkiaDrawView::setDebugMode),
        makeNativeMethod("updateTouchPoints",
                         JniSkiaDrawView::updateTouchPoints),
        makeNativeMethod("registerView", JniSkiaDrawView::registerView),
        makeNativeMethod("unregisterView", JniSkiaDrawView::unregisterView),
        // TODO: Remove if we find another solution for first frame rendering
        // makeNativeMethod("renderToBitmap", JniSkiaDrawView::renderToBitmap)
    });
  }

protected:
  void updateTouchPoints(jni::JArrayDouble touches) override {
    JniSkiaBaseView::updateTouchPoints(touches);
  }

  void surfaceAvailable(jobject surface, int width, int height) override {
    JniSkiaBaseView::surfaceAvailable(surface, width, height);
  }

  void surfaceSizeChanged(int width, int height) override {
    JniSkiaBaseView::surfaceSizeChanged(width, height);
  }

  void surfaceDestroyed() override { JniSkiaBaseView::surfaceDestroyed(); }

  void setMode(std::string mode) override { JniSkiaBaseView::setMode(mode); }

  void setDebugMode(bool show) override { JniSkiaBaseView::setDebugMode(show); }

  void registerView(int nativeId) override {
    JniSkiaBaseView::registerView(nativeId);
  }

  void unregisterView() override { JniSkiaBaseView::unregisterView(); }

  // TODO: Remove if we find another solution for first frame rendering
  /*jobject renderToBitmap(jobject bitmap, int width, int height) override {
    return JniSkiaBaseView::renderToBitmap(bitmap, width, height);
  }*/

private:
  friend HybridBase;

  explicit JniSkiaDrawView(
      jni::alias_ref<jhybridobject> jThis,
      jni::alias_ref<JniSkiaManager::javaobject> skiaManager)
      : JniSkiaBaseView(skiaManager,
                        std::make_shared<RNSkAndroidView<RNSkia::RNSkJsView>>(
                            skiaManager->cthis()->getPlatformContext())) {}

  jni::global_ref<javaobject> javaPart_;
};

} // namespace RNSkia
