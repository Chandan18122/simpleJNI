package com.einfochips.JNI;

public class Result {
    private int roll;
    private String status;
    private String grade;

    public Result(int roll, String status, String grade) {
        this.roll = roll;
        this.status = status;
        this.grade = grade;
    }

    public int getRoll() {
        return roll;
    }

    public void setRoll(int roll) {
        this.roll = roll;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getGrade() {
        return grade;
    }

    public void setGrade(String grade) {
        this.grade = grade;
    }
}
