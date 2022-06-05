#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>

using namespace ultralight;

const char* htmlString_LeftPane();
const char* htmlString_RightPane();

#define WINDOW_WIDTH    900
#define WINDOW_HEIGHT   600
#define LEFT_PANE_WIDTH 200

///
/// Welcome to Sample 3!
///
/// In this sample we'll continue working with the AppCore API and show
/// how to make your app responsive to changes in window size by updating the
/// layout of multiple overlays.
///
/// We will create a window with two overlays-- a left pane with a fixed width
/// and a right pane that takes up the remaining width.
///
///    +----------------------------------------------------+
///    |               |                                    |
///    |               |                                    |
///    |               |                                    |
///    |               |                                    |
///    |               |                                    |
///    |   Left Pane   |             Right Pane             |
///    |    (200px)    |              (Fluid)               |
///    |               |                                    |
///    |               |                                    |
///    |               |                                    |
///    |               |                                    |
///    |               |                                    |
///    +----------------------------------------------------+
/// 
/// To respond to resize events, we'll attach a WindowListener to our window
/// and re-calculate layout of our overlays in the OnResize callback.
///

class MyApp : public WindowListener,
              public ViewListener {
  RefPtr<App> app_;
  RefPtr<Window> window_;
  RefPtr<Overlay> pane_;
public:
  MyApp() {
    ///
    /// Create our main App instance.
    ///
    app_ = App::Create();

    ///
    /// Create a resizable window by passing by OR'ing our window flags with
    /// kWindowFlags_Resizable.
    ///
    window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
      false, kWindowFlags_Titled | kWindowFlags_Resizable);

    ///
    /// Set the title of our window.
    ///
    window_->SetTitle("AZS");

    ///
    /// Tell our app to use 'window' as our main window.
    ///
    /// This call is required before creating any overlays or calling App::Run
    ///
    app_->set_window(*window_.get());

    ///
    /// Create the overlays for our left and right panes-- we don't care about
    /// their initial size and position because they'll be set when we call
    /// OnResize() below.
    ///
    pane_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);

    ///
    /// Force a call to OnResize to perform initial layout and sizing of our
    /// left and right overlays.
    ///
    OnResize(window_->width(), window_->height());

    ///
    /// Load some HTML into our left and right overlays.
    ///
    pane_->view()->LoadURL("file:///index.html");

    ///
    /// Register our MyApp instance as a WindowListener so we can handle the
    /// Window's OnResize event below.
    ///
    window_->set_listener(this);

    ///
    /// Register our MyApp instance as a ViewListener so we can handle the
    /// Views' OnChangeCursor event below.
    ///
    pane_->view()->set_view_listener(this);
  }

  virtual ~MyApp() {}

  ///
  /// Inherited from WindowListener, not used.
  ///
  virtual void OnClose() override {}

  ///
  /// Inherited from WindowListener, called when the Window is resized.
  ///
  virtual void OnResize(uint32_t width, uint32_t height) override {
    pane_->Resize(width, height);

  }

  ///
  /// Inherited from ViewListener, called when the Cursor changes.
  ///
  virtual void OnChangeCursor(ultralight::View* caller,
    Cursor cursor) {
    window_->SetCursor(cursor);
  }

  void Run() {
    app_->Run();
  }
};

int main() {
  MyApp app;
  app.Run();

  return 0;
}


