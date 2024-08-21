package com.einfochips.JNI

import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.einfochips.JNI.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity(), View.OnClickListener {

    private lateinit var binding: ActivityMainBinding
    private lateinit var student: Student

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        // Initialize a sample student
        student = createSampleStudent()

        // Set click listeners
        binding.addButton.setOnClickListener(this)
        binding.randomNumButton.setOnClickListener(this)
        binding.getStudentDetailsButton.setOnClickListener(this)
        binding.getResultButton.setOnClickListener(this)
        binding.studentFromBundleButton.setOnClickListener(this)
        binding.arrayListOfStudentsResultButton.setOnClickListener(this)
        binding.studentEnumButton.setOnClickListener(this)
        binding.basicTypeButton.setOnClickListener(this)
    }

    private fun createSampleStudent(): Student {
        val marksList = arrayListOf(
            Marks("Math", 96),
            Marks("English", 65),
            Marks("Hindi", 80)
        )
        return createStudentJNI(1, "Chandan Kumar", 24, 85, marksList)
    }

    override fun onClick(v: View?) {
        when (v?.id) {
            R.id.addButton -> handleAddButtonClick()
            R.id.randomNumButton -> handleRandomNumButtonClick()
            R.id.getStudentDetailsButton -> handleGetStudentDetailsButtonClick()
            R.id.getResultButton -> handleGetResultButtonClick()
            R.id.studentFromBundleButton -> handleStudentFromBundleButtonClick()
            R.id.arrayListOfStudentsResultButton -> handleArrayListOfStudentsResultButtonClick()
            R.id.studentEnumButton -> handleStudentEnumButtonClick()
            R.id.basicTypeButton -> handleBasicTypeButtonClick()
        }
    }

    private fun handleAddButtonClick() {
        val num1 = binding.editTextNumber1.text.toString().toIntOrNull() ?: 0
        val num2 = binding.editTextNumber2.text.toString().toIntOrNull() ?: 0
        binding.sampleText.text = "$num1 + $num2 = ${addTwoNumberJNI(num1, num2)}"
        binding.editTextNumber1.text?.clear()
        binding.editTextNumber2.text?.clear()
    }

    private fun handleRandomNumButtonClick() {
        binding.sampleText.text = "Random number: ${randomNumberJNI()}"
    }

    private fun handleGetStudentDetailsButtonClick() {
        binding.sampleText.text = getStudentDetailsJNI(student)
    }

    private fun handleGetResultButtonClick() {
        val result = getResultJNI(student)
        binding.sampleText.text = "Roll: ${result.roll}, Result: ${result.status}, Score: ${result.grade}"
    }

    private fun handleStudentFromBundleButtonClick() {
        val bundle = Bundle().apply {
            putParcelable("student", student)
        }
        binding.sampleText.text = "Student from Bundle: ${createStudentFromBundleJNT(bundle)}"
    }

    private fun handleArrayListOfStudentsResultButtonClick() {
        val studentList = arrayListOf(
            Student(1, "Chandan Kumar", 24, 95),
            Student(2, "Ranjan Kumar", 21, 90)
        )
        binding.sampleText.text = "Student List: ${sendStudentsJNI(studentList)}"
    }

    private fun handleStudentEnumButtonClick() {
        binding.sampleText.text = "Student ENUM: ${sendStudentEnumJNT(StudentEnum.SENIOR)}, ${sendStudentEnumJNT(StudentEnum.JUNIOR)}"
    }

    private fun handleBasicTypeButtonClick() {
        binding.sampleText.text = "Basic Type: ${basicTypes(12, 232232L, true, 42.2F, 232.22, "Chandan")}"
    }

    /**
     * A native method that is implemented by the 'JNI' native library,
     * which is packaged with this application.
     */
    private external fun stringFromJNI(): String
    private external fun addTwoNumberJNI(num1: Int, num2: Int): Int
    private external fun randomNumberJNI(): Int
    private external fun getStudentDetailsJNI(student: Student): String
    private external fun createStudentJNI(roll: Int, name: String, age: Int, score: Int, marks: List<Marks>): Student
    private external fun getResultJNI(student: Student): Result
    private external fun createStudentFromBundleJNT(bundle: Bundle): String
    private external fun sendStudentsJNI(list: List<Student>): String
    private external fun sendStudentEnumJNT(studentEnum: StudentEnum): Int
    private external fun basicTypes(anInt: Int, aLong: Long, aBoolean: Boolean, aFloat: Float, aDouble: Double, aString: String) : Boolean
    companion object {
        // Used to load the 'JNI' library on application startup.
        init {
            System.loadLibrary("JNI")
        }
    }
}
