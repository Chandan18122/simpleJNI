package com.einfochips.JNI;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.NonNull;

public class Marks implements Parcelable {
    private String subjectName;
    private int subjectMark;

    public Marks(String subjectName, int subjectMark) {
        this.subjectName = subjectName;
        this.subjectMark = subjectMark;
    }

    protected Marks(Parcel in) {
        subjectName = in.readString();
        subjectMark = in.readInt();
    }

    public static final Creator<Marks> CREATOR = new Creator<Marks>() {
        @Override
        public Marks createFromParcel(Parcel in) {
            return new Marks(in);
        }

        @Override
        public Marks[] newArray(int size) {
            return new Marks[size];
        }
    };

    public String getSubjectName() {
        return subjectName;
    }

    public void setSubjectName(String subjectName) {
        this.subjectName = subjectName;
    }

    public int getSubjectMark() {
        return subjectMark;
    }

    public void setSubjectMark(int subjectMark) {
        this.subjectMark = subjectMark;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(@NonNull Parcel dest, int flags) {
        dest.writeString(subjectName);
        dest.writeInt(subjectMark);
    }
}
