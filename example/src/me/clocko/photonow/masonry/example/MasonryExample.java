package me.clocko.photonow.masonry.example;

import android.app.Activity;
import android.os.Bundle;
import me.clocko.photonow.masonry.Masonry;

public class MasonryExample extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        Masonry.masonry(1, null);
    }
}
