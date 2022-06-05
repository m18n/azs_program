package com.example.azs;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.webkit.WebView;
import android.widget.TextView;

import com.example.azs.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'azs' library on application startup.
    static {
        System.loadLibrary("azs");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        WebView web=(WebView)findViewById(R.id.webview);
        web.getSettings().setJavaScriptEnabled(true);
        web.loadUrl("file:///android_asset/www/index.html");
    }

    /**
     * A native method that is implemented by the 'azs' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}