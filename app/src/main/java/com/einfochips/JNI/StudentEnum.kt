package com.einfochips.JNI

import java.io.Serializable

enum class StudentEnum(val id: Int) : Serializable {
    JUNIOR(123),
    SENIOR(456);
}