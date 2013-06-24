package me.clocko.photonow.masonry;

import java.util.List;

public final class Masonry {
    static {
        System.loadLibrary("masonry");
    }

    public static native List<DiscreteRect> masonry (final int gridWidth, final List<DiscreteRect> photos);
}
