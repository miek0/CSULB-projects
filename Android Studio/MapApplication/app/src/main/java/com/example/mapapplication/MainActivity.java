/**
 * Justin Mabutas, Mike Zeng
 * CECS 453
 * HW3
 */
package com.example.mapapplication;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.mapbox.android.core.permissions.PermissionsListener;
import com.mapbox.android.core.permissions.PermissionsManager;
import com.mapbox.mapboxsdk.Mapbox;
import com.mapbox.mapboxsdk.annotations.Marker;
import com.mapbox.mapboxsdk.annotations.MarkerOptions;
import com.mapbox.mapboxsdk.camera.CameraUpdateFactory;
import com.mapbox.mapboxsdk.geometry.LatLng;
import com.mapbox.mapboxsdk.location.LocationComponent;
import com.mapbox.mapboxsdk.location.LocationComponentActivationOptions;
import com.mapbox.mapboxsdk.location.modes.CameraMode;
import com.mapbox.mapboxsdk.location.modes.RenderMode;
import com.mapbox.mapboxsdk.maps.MapboxMap;
import com.mapbox.mapboxsdk.maps.OnMapReadyCallback;
import com.mapbox.mapboxsdk.maps.Style;
import com.mapbox.mapboxsdk.maps.SupportMapFragment;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.LinkedList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements
        OnMapReadyCallback, PermissionsListener {

    //    Car List Adapter is to be passed into the CarRecyclerView.
    class LocationListAdapter extends
            RecyclerView.Adapter<LocationListAdapter.LocationViewHolder> {

        private final LinkedList<Pair<String, LatLng>> mLocationList;
        private final LayoutInflater mInflater;

        class LocationViewHolder extends RecyclerView.ViewHolder
                implements View.OnClickListener {

            final TextView locationItemView;
            final LocationListAdapter mAdapter;

            /**
             * Creates a new custom view holder to hold the view to display in the RecyclerView.
             *
             * @param itemView The view in which to display the data.
             * @param adapter The adapter that manages the the data and views for the RecyclerView.
             */
            public LocationViewHolder(View itemView, LocationListAdapter adapter) {
                super(itemView);
                locationItemView = (TextView) itemView.findViewById(R.id.location);
                this.mAdapter = adapter;
                itemView.setOnClickListener(this);
            }

            //Whenever an item is clicked in the recycler view, this runs
            @Override
            public void onClick(View v) {
                int itemPosition = location_list_rv.getChildLayoutPosition(v);  //Get the item position of what was clicked.
                Pair<String, LatLng> item = location_list.get(itemPosition);    //Get the details from the array
                LatLng item_location = item.second;
                if(destination_marker!=null)        //if there is a marker on the map at this time
                    destination_marker.remove();
                destination_marker = mapbox_map.addMarker(new MarkerOptions().position(item_location));
                search_bar.setText(item.first);
                mapbox_map.moveCamera(CameraUpdateFactory.newLatLngZoom(item_location, search_zoom));
            }
        }

        public LocationListAdapter(Context context, LinkedList<Pair<String, LatLng>> wordList) {
            mInflater = LayoutInflater.from(context);
            this.mLocationList = wordList;
        }

        /**
         * Inflates an item view and returns a new view holder that contains it.
         * Called when the RecyclerView needs a new view holder to represent an item.
         *
         * @param parent The view group that holds the item views.
         * @param viewType Used to distinguish views, if more than one
         *                 type of item view is used.
         * @return a view holder.
         */
        @Override
        public LocationViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            // Inflate an item view.
            View itemView = mInflater.inflate(R.layout.location_list_item, parent, false);
            return new LocationViewHolder(itemView, this);
        }

        /**
         * Sets the contents of an item at a given position in the RecyclerView.
         *
         * @param holder The view holder for that position in the RecyclerView.
         * @param position The position of the item in the RecycerView.
         */
        @Override
        public void onBindViewHolder(LocationViewHolder holder, int position) {
            // Retrieve the data for that position.
            Pair<String, LatLng> current = mLocationList.get(position);
            // Add the data to the view holder.
            holder.locationItemView.setText((position+1) + ":  " + current.first);
        }

        /**
         * Returns the size of the container that holds the data.
         * @return Size of the list of data.
         */
        @Override
        public int getItemCount() {
            return mLocationList.size();
        }

        @Override
        public long getItemId(int position) {
            return super.getItemId(position);
        }

        @Override
        public int getItemViewType(int position) {
            return super.getItemViewType(position);
        }
    }

    //views and data structures
    private PermissionsManager permissions_manager;
    private MapboxMap mapbox_map;
    private EditText search_bar;
    private float init_zoom = 12f;
    private float search_zoom = 15f;
    private Button search_button;
    private Double current_latitude, current_longitude;
    private boolean location_exists;
    private RecyclerView location_list_rv;
    private LocationListAdapter location_list_adapter;
    private final LinkedList<Pair<String, LatLng>> location_list = new LinkedList<>();
    private String TAG = MainActivity.class.getSimpleName();
    private Marker destination_marker;
    private String[] parse_place_name;
    private String place_name;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//          Mapbox access token is configured here. This needs to be called either in your application object or in the same activity which contains the mapview.
        Mapbox.getInstance(this, getString(R.string.mapbox_access_token));
//          Set Content View to activity_main
        setContentView(R.layout.activity_main);
        SupportMapFragment map_fragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map_fragment);
        map_fragment.getMapAsync(this);

//        Initialize components
        search_bar = findViewById(R.id.search_bar);
        search_bar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                search_bar.setText("");
            }
        });
        search_button = findViewById(R.id.search_button);
        search_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new GeoCodeService().execute(search_bar.getText().toString());
            }
        });
        location_list_rv = findViewById(R.id.location_list_rv);
        location_list_rv.setLayoutManager(new LinearLayoutManager(this));
        location_list_adapter = new LocationListAdapter(this, location_list);
        location_list_rv.setAdapter(location_list_adapter);
    }

    @Override
    public void onMapReady(MapboxMap mapboxMap) {
        mapbox_map = mapboxMap;
        mapbox_map.setStyle(Style.MAPBOX_STREETS,
                new Style.OnStyleLoaded() {
                    @Override
                    public void onStyleLoaded(Style style) {
                        enableLocationComponent(style);
//                        Location of CSULB
                        LatLng location = new LatLng(33.784294,-118.120983);
                        mapbox_map.moveCamera(CameraUpdateFactory.newLatLngZoom(location, init_zoom));
                    }
                });
    }

    @SuppressWarnings( {"MissingPermission"})
    private void enableLocationComponent(Style loadedMapStyle) {
// Check if permissions are enabled and if not request
        if (PermissionsManager.areLocationPermissionsGranted(this)) {

// Get an instance of the component
            LocationComponent locationComponent = mapbox_map.getLocationComponent();

// Activate with options
            locationComponent.activateLocationComponent(
                    LocationComponentActivationOptions.builder(this, loadedMapStyle).build());

// Enable to make component visible
            locationComponent.setLocationComponentEnabled(true);

// Set the component's camera mode
            locationComponent.setCameraMode(CameraMode.TRACKING);

// Set the component's render mode
            locationComponent.setRenderMode(RenderMode.COMPASS);
        } else {
            permissions_manager = new PermissionsManager(this);
            permissions_manager.requestLocationPermissions(this);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        permissions_manager.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    @Override
    public void onExplanationNeeded(List<String> permissionsToExplain) {
        Toast.makeText(this, "We require location permission.", Toast.LENGTH_LONG).show();
    }

    @Override
    public void onPermissionResult(boolean granted) {
        if (granted) {
            mapbox_map.getStyle(new Style.OnStyleLoaded() {
                @Override
                public void onStyleLoaded(Style style) {
                    enableLocationComponent(style);
                }
            });
        } else {
            Toast.makeText(this, "User location permission not granted.", Toast.LENGTH_LONG).show();
            finish();
        }
    }

    /*
     * allows us to navigate on the map via mapbox
     */
    private class GeoCodeService extends AsyncTask<String, Void, LatLng> {

        //calls this when a place is nonexistent (unsearchable in the mapbox query)
        protected void openErrorDialog(){
            ErrorDialog error = new ErrorDialog();
            error.show(getSupportFragmentManager(), "error message");
        }

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
        }

        @Override
        protected LatLng doInBackground(String... search_location) {

            String url_front = "https://api.mapbox.com/geocoding/v5/mapbox.places/";
            String url_middle = search_location[0];
            String url_end = ".json?limit=1&country=US&access_token=pk.eyJ1IjoidGhpc2p1aWNldGluIiwiYSI6ImNrOTB2ZzVsZDA2MDYzcHVnMHV2OXd4aWkifQ.ng9JZtzt3lHOAf0EbIU6wA";
            JSONArray latlon;
            HttpHandler sh = new HttpHandler();

//            Format url_middle;
            url_middle = url_middle.replace(" ", "%20");
            Log.e(TAG, url_middle);
            // Making a request to url and getting response
            String url = url_front + url_middle + url_end;
            String jsonStr = sh.makeServiceCall(url);

            Log.e(TAG, "Response from url: " + jsonStr);

            if (jsonStr != null) {
                try {
                    JSONObject jsonObj = new JSONObject(jsonStr);

                    // Getting JSON Array node
                    JSONArray address = jsonObj.getJSONArray("features");
                    if(address.length() < 1) {
                        location_exists=false;
                        return null;
                    }

                    for (int i =0; i<address.length(); i++)
                    {
                        JSONObject c = address.getJSONObject(i);
                        latlon =  c.getJSONArray("center");
                        //coordinates
                        current_latitude = latlon.getDouble(1);
                        current_longitude = latlon.getDouble(0);
                        Log.e(TAG, current_latitude + " " + current_longitude);
                        LatLng location = new LatLng(current_latitude,current_longitude);
                        //place name
                        parse_place_name = c.getString("place_name").split(",", 0);
                        place_name = parse_place_name[0]+", "+parse_place_name[1];  //when there is a matching query to the location, the place's name is stored into the list
                        location_exists=true;
                        return location;
                    }

                } catch (final JSONException e) {
                    Log.e(TAG, "Json parsing error: " + e.getMessage());
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(getApplicationContext(),
                                    "Json parsing error: " + e.getMessage(),
                                    Toast.LENGTH_LONG)
                                    .show();
                        }
                    });
                    location_exists=false;
                }
            }

            return null;
        }

        @Override
        protected void onPostExecute(LatLng result) {
            super.onPostExecute(result);
            if(location_exists){
                if(result!=null) {
                    if(destination_marker!=null)        //if there is a marker on the map at this time
                        destination_marker.remove();
                    //places the new marker
                    destination_marker = mapbox_map.addMarker(new MarkerOptions().position(result));

                    mapbox_map.moveCamera(CameraUpdateFactory.newLatLngZoom(result, search_zoom));
                    //Add the valid location to a recycler view at the bottom of the screen.
                    //searches are only added if not duplicate
                    Pair<String, LatLng> search_value = new Pair<>(place_name, new LatLng(result.getLatitude(), result.getLongitude()));
                    if(!location_list.contains(search_value)){
                        location_list.add(search_value);
                    }
                    location_list_adapter.notifyDataSetChanged();
                }
            }else{
                openErrorDialog();  //if the place doesn't exist in map directories
            }
        }
    }
}
