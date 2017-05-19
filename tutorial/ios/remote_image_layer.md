---
title: Remote Image Layer
layout: ios-tutorial
---

The Geography Class example only has a few levels of detail.  We can't zoom in very close and if we could it would take up way too much space on the device.  Thus, we need a way to look at tiled image maps sitting on a server.

![Stamen Terrain]({{ site.baseurl }}/images/tutorial/remote_image_layer_1.png)

Let's add a remote tile source, and take a closer look at the Earth. We'll use the Stamen Terrain tile set. If you end up wanting to use these tiles in an app that you distribute, check out the [requirements](http://maps.stamen.com/#terrain). (Full attribution: Map tiles by [Stamen Design](http://stamen.com/), under [CC BY 3.0](http://creativecommons.org/licenses/by/3.0). Data by [OpenStreetMap](http://openstreetmap.org/), under [ODbL](http://www.openstreetmap.org/copyright).)

You'll need to have done the [Local Image Layer](local_image_tiles.html) tutorial.  Open your HelloEarth project and get ready.

![Xcode ViewController.m]({{ site.baseurl }}/images/tutorial/local_image_layer_1.png)

If you haven't got one here is a suitable ViewController (for [Objective-C]({{ site.baseurl }}/tutorial/ios/code/ViewController_remote_image_layer.m) or [Swift]({{ site.baseurl }}/tutorial/ios/code/ViewController_remote_image_layer.swift)) file to start with.  This version handles both a globe and a map and makes a nice starting point.

### Remote Tile Source

We'll set this up to use either the local or remote tiles. Look for the following lines in your source code.

{% multiple_code %}
  {% highlight objc %}
// Set up the layer
MaplyMBTileSource *tileSource = 
    [[MaplyMBTileSource alloc] initWithMBTiles:@"geography-­class_medres"];

MaplyQuadImageTilesLayer *layer = 
    [[MaplyQuadImageTilesLayer alloc] initWithCoordSystem:tileSource.coordSys 
                                      tileSource:tileSource];
  {% endhighlight %}

  {----}

  {% highlight swift %}
// set up the data source
if let tileSource = MaplyMBTileSource(MBTiles: "geography-class_medres"),
        // set up the layer
        layer = MaplyQuadImageTilesLayer(tileSource: tileSource) {

}
  {% endhighlight %}
{% endmultiple_code %}


Now replace that with these lines instead.  This will let you use either local or remote data.

{% multiple_code %}
  {% highlight objc %}
// add the capability to use the local tiles or remote tiles
bool useLocalTiles = false;

// we'll need this layer in a second
MaplyQuadImageTilesLayer *layer;

if (useLocalTiles)
{
  MaplyMBTileSource *tileSource = 
        [[MaplyMBTileSource alloc] initWithMBTiles:@"geography­-class_medres"];
  layer = [[MaplyQuadImageTilesLayer alloc] 
                initWithCoordSystem:tileSource.coordSys tileSource:tileSource];
} else {
  // Because this is a remote tile set, we'll want a cache directory
  NSString *baseCacheDir = 
    [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) 
            objectAtIndex:0];
  NSString *tilesCacheDir = [NSString stringWithFormat:@"%@/stamentiles/",
                                                baseCacheDir];
  int maxZoom = 18;

  // Stamen Terrain Tiles, courtesy of Stamen Design under the Creative Commons Attribution License.
  // Data by OpenStreetMap under the Open Data Commons Open Database License.
  MaplyRemoteTileSource *tileSource = 
    [[MaplyRemoteTileSource alloc] 
            initWithBaseURL:@"http://tile.stamen.com/terrain/" 
            ext:@"png" minZoom:0 maxZoom:maxZoom];
  tileSource.cacheDir = tilesCacheDir;
  layer = [[MaplyQuadImageTilesLayer alloc] 
            initWithCoordSystem:tileSource.coordSys tileSource:tileSource];
}
  {% endhighlight %}

  {----}

  {% highlight swift %}
// add the capability to use the local tiles or remote tiles
let useLocalTiles = false

// we'll need this layer in a second
let layer: MaplyQuadImageTilesLayer

if useLocalTiles {
    guard let tileSource = MaplyMBTileSource(MBTiles: "geography-class_medres") else {
        // can't load local tile set
    }
    layer = MaplyQuadImageTilesLayer(tileSource: tileSource)!
}
else {
    // Because this is a remote tile set, we'll want a cache directory
    let baseCacheDir = NSSearchPathForDirectoriesInDomains(.CachesDirectory, .UserDomainMask, true)[0]
    let tilesCacheDir = "\(baseCacheDir)/stamentiles/"
    let maxZoom = Int32(18)

    // Stamen Terrain Tiles, courtesy of Stamen Design under the Creative Commons Attribution License.
    // Data by OpenStreetMap under the Open Data Commons Open Database License.
    guard let tileSource = MaplyRemoteTileSource(
            baseURL: "http://tile.stamen.com/terrain/",
            ext: "png",
            minZoom: 0, 
            maxZoom: maxZoom) else {
        // can't create remote tile source
        return
    }
    tileSource.cacheDir = tilesCacheDir
    layer = MaplyQuadImageTilesLayer(tileSource: tileSource)!
}
  {% endhighlight %}
{% endmultiple_code %}

Don't forget the call to addLayer below this.  We're just creating a slightly different data source, we still need to add the layer to the globe or map.

There's only one important change here.  Rather than use a MaplyMBTileSource we create a MaplyRemoteTileSource.  It does just what it sounds like, loads its tiles from a remote source.

We also set up a cache for the tiles because it's rude to thrash the server.  We set up the MaplyQuadImageTilesLayer as before.  It can handle a variety of data sources.

And finally, if you're running iOS 9 or later, you'll need to configure the app to be allowed to make HTTP requests. If not, only HTTPS requests are allowed. Just open your Info.plist file, and add the key "App Transport Security Settings". Inside that, add "Allow Arbitrary Loads" key with value "YES".

![App Transport Security Settings]({{ site.baseurl }}/images/tutorial/remote_image_layer_3.png)


### Build and Run

Give it a try.  It's even more fun on a device. You can zoom in to your heart's content, provided your heart doesn't desire sub­meter resolution.

![Stamen Terrain in Simulator]({{ site.baseurl }}/images/tutorial/remote_image_layer_2.png)

All that with just a few lines of code.  WhirlyGlobe-Maply is doing a lot of work behind the scenes.  As you move around it pulls in new data, caches it to the local device, displays it, gets rid of the old data and so forth.  But setting all this up is easy.

Next up, let’s overlay some data on here.  How about some vectors?