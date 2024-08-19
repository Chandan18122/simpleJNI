package com.einfochips.JNI

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
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

        val student : Student = createStudentJNI(1, "Chandan Kumar", 24, 85)
        binding.getStudentDetailsButton.setOnClickListener {
            binding.sampleText.text = "${getStudentDetailsJNI(student)}"
        }

        binding.getResultButton.setOnClickListener {
            val result = getResultJNI(student)
            binding.sampleText.text = "Roll: ${result.roll}, Result: ${result.status}, Score: ${result.grade}"
        }
    }

    /**
     * A native method that is implemented by the 'JNI' native library,
     * which is packaged with this application.
     */
    private external fun stringFromJNI(): String
    private external fun addTwoNumberJNI(num1: Int, num2: Int): Int
    private external fun randomNumberJNI(): Int
    private external fun getStudentDetailsJNI(student: Student): String
    private external fun createStudentJNI(roll: Int, name: String, age: Int, score: Int): Student
    private external fun getResultJNI(student: Student): Result
    companion object {
        // Used to load the 'JNI' library on application startup.
        init {
            System.loadLibrary("JNI")
        }
    }
}

data class Student(val roll: Int, val name: String, val age: Int, val score: Int)
data class Result(val roll: Int, val status: String, val grade: String)