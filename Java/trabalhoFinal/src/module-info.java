module trabalhoFinal {
    requires javafx.fxml;
    requires javafx.controls;
    requires javafx.graphics;

    opens poomail;
    opens poomail.controllers;
    opens poomail.scenes;
    opens poomail.style;
    opens poomail.classes;
    opens poomail.data;
    opens poomail.holders;
}