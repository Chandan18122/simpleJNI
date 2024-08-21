package com.einfochips.JNI;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.NonNull;

import java.util.List;

public class Student implements Parcelable {
    private int roll;
    private String name;
    private int age;
    private int score;
    private List<Marks> marks ;

    public Student(int roll, String name, int age, int score) {
        this.roll = roll;
        this.name = name;
        this.age = age;
        this.score = score;
    }
    public Student(int roll, String name, int age, int score, List<Marks> marks) {
        this.roll = roll;
        this.name = name;
        this.age = age;
        this.score = score;
        this.marks = marks;
    }

    protected Student(Parcel in) {
        roll = in.readInt();
        name = in.readString();
        age = in.readInt();
        score = in.readInt();
        marks = in.createTypedArrayList(Marks.CREATOR);
    }

    public static final Creator<Student> CREATOR = new Creator<Student>() {
        @Override
        public Student createFromParcel(Parcel in) {
            return new Student(in);
        }

        @Override
        public Student[] newArray(int size) {
            return new Student[size];
        }
    };

    public int getRoll() {
        return roll;
    }

    public void setRoll(int roll) {
        this.roll = roll;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public List<com.einfochips.JNI.Marks> getMarks() {
        return marks;
    }

    public void setMarks(List<com.einfochips.JNI.Marks> marks) {
        this.marks = marks;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(@NonNull Parcel dest, int flags) {
        dest.writeInt(roll);
        dest.writeString(name);
        dest.writeInt(age);
        dest.writeInt(score);
        dest.writeTypedList(marks);
    }
}
