package com.einfochips.JNI;

import java.io.Serializable;

public enum StudentEnum implements Serializable {
    JUNIOR(123),
    SENIOR(456);

    private final int id;

    StudentEnum(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }
}
