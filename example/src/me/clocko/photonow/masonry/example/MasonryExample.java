package me.clocko.photonow.masonry.example;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import me.clocko.photonow.masonry.DiscreteRect;
import me.clocko.photonow.masonry.Masonry;

import java.util.ArrayList;
import java.util.List;

public class MasonryExample extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        List<DiscreteRect> someRects = new ArrayList<DiscreteRect>();
        someRects.add(new DiscreteRect(0, 0, 1, 1));
        someRects.add(new DiscreteRect(0, 0, 2, 1));
        someRects.add(new DiscreteRect(0, 0, 1, 5));

        List<DiscreteRect> result = Masonry.masonry(2, someRects);

        for (DiscreteRect rect: result) {
            Log.d("Masonry", String.format("%d, %d, %d, %d", rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight()));
        }
    }
}
