#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>

using namespace ultralight;

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600


class MyApp : public WindowListener,
              public ViewListener
{
  RefPtr<App> app_;
  RefPtr<Window> window_;
  RefPtr<Overlay> pane_;

public:
  MyApp()
  {

    app_ = App::Create();

    window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                             false, kWindowFlags_Titled | kWindowFlags_Resizable | kWindowFlags_Maximizable);

    window_->SetTitle("AZS");

    app_->set_window(*window_.get());

    pane_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);

    OnResize(window_->width(), window_->height());

    pane_->view()->LoadURL("file:///index.html");

    window_->set_listener(this);

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
  virtual void OnResize(uint32_t width, uint32_t height) override
  {
    pane_->Resize(width, height);
  }

  ///
  /// Inherited from ViewListener, called when the Cursor changes.
  ///
  virtual void OnChangeCursor(ultralight::View *caller,
                              Cursor cursor)
  {
    window_->SetCursor(cursor);
  }

  void Run()
  {
    app_->Run();
  }
};

int main()
{
  MyApp app;
  app.Run();

  return 0;
}
