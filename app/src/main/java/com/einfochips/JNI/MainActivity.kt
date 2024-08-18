package com.einfochips.JNI

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.einfochips.JNI.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        binding.addButton.setOnClickListener {
            val num1 = binding.editTextNumber1.text.toString().toIntOrNull() ?: 0
            val num2 = binding.editTextNumber2.text.toString().toIntOrNull() ?: 0
            binding.sampleText.text = "$num1 + $num2 = ${addTwoNumberJNI(num1, num2)}"
            binding.editTextNumber1.text?.clear()
            binding.editTextNumber2.text?.clear()

        }

        binding.randomNumButton.setOnClickListener {
            binding.sampleText.text = "Random number : ${randomNumberJNI()}"
        }

    }

    /**
     * A native method that is implemented by the 'JNI' native library,
     * which is packaged with this application.
     */
    private external fun stringFromJNI(): String
    private external fun addTwoNumberJNI(num1: Int, num2: Int): Int
    private external fun randomNumberJNI(): Int

    companion object {
        // Used to load the 'JNI' library on application startup.
        init {
            System.loadLibrary("JNI")
        }
    }
}