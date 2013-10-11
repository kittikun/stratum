package com.kittikun.stratum;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.app.AlertDialog;

public class StratumActivity extends Activity {

	  // load the library - name matches jni/Android.mk 
	static {
	  System.loadLibrary("stratum");
	}

	  // declare the native code function - must match ndkfoo.c
	private native String invokeNativeFunction();
   
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stratum);

        // this is where we call the native code
	    String hello = invokeNativeFunction();
	         
	    new AlertDialog.Builder(this).setMessage(hello).show();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.stratum, menu);
        return true;
    }
    
    
    
}
