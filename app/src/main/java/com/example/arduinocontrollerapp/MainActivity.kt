package com.example.arduinocontrollerapp

import android.Manifest
import android.content.pm.PackageManager
import android.location.Location
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.android.volley.Request
import com.android.volley.RequestQueue
import com.android.volley.Response
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley
import com.google.android.gms.location.FusedLocationProviderClient
import com.google.android.gms.location.LocationServices
import com.google.android.gms.tasks.OnSuccessListener

class MainActivity : AppCompatActivity() {

    private lateinit var fusedLocationClient: FusedLocationProviderClient
    private lateinit var requestQueue: RequestQueue
    private lateinit var tvGpsLocation: TextView
    private val serverIp = "http://192.168.4.1" // Replace with your ESP8266 IP address

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val btnStartEngine = findViewById<Button>(R.id.btnStartEngine)
        val btnStopEngine = findViewById<Button>(R.id.btnStopEngine)
        val btnControlRelay = findViewById<Button>(R.id.btnControlRelay)
        tvGpsLocation = findViewById(R.id.tvGpsLocation)

        requestQueue = Volley.newRequestQueue(this)
        fusedLocationClient = LocationServices.getFusedLocationProviderClient(this)

        // Start engine
        btnStartEngine.setOnClickListener {
            sendCommandToArduino("/startEngine")
        }

        // Stop engine
        btnStopEngine.setOnClickListener {
            sendCommandToArduino("/stopEngine")
        }

        // Toggle relay
        btnControlRelay.setOnClickListener {
            sendCommandToArduino("/toggleRelay")
        }

        // Get GPS location
        getGpsLocation()
    }

    private fun sendCommandToArduino(endpoint: String) {
        val url = "$serverIp$endpoint"
        val stringRequest = StringRequest(Request.Method.GET, url,
            Response.Listener { response ->
                Log.d("ArduinoController", "Response: $response")
            },
            Response.ErrorListener { error ->
                Log.e("ArduinoController", "Error: ${error.message}")
            })
        requestQueue.add(stringRequest)
    }

    private fun getGpsLocation() {
        if (ActivityCompat.checkSelfPermission(
                this,
                Manifest.permission.ACCESS_FINE_LOCATION
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.ACCESS_FINE_LOCATION), 1)
            return
        }

        fusedLocationClient.lastLocation
            .addOnSuccessListener(this, OnSuccessListener<Location> { location ->
                if (location != null) {
                    val locationText = "Lat: ${location.latitude}, Lon: ${location.longitude}"
                    tvGpsLocation.text = "GPS Location: $locationText"
                }
            })
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == 1 && grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
            getGpsLocation()
        }
    }
}
