package poomail.controllers;

import javafx.application.Platform;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import poomail.Main;
import poomail.classes.User;
import poomail.classes.UserHolder;

import java.io.IOException;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Path;



public class ControllerLogin {

    private User user;

    @FXML
    private TextField loginField;
    @FXML
    private BorderPane scene;
    @FXML
    private Button loginButton;



    public ControllerLogin() {
        changeFocus();
    }

    @FXML
    public void initialize (){
        scene.requestFocus();
    }


    // EventsHandler
    @FXML
    public void loginAction(){
        user = new User(loginField.getText());
        if (!user.toString().equals("")) {
            openEmail(true, user);
        }else {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText("Favor informar um usuario");
            alert.show();
        }
    }

    @FXML
    public void textAction(){
        loginAction();
    }

    // Methods
    private void changeFocus (){
        Platform.runLater( () -> scene.requestFocus());
    }

    private void openEmail(boolean confirmaLogin, User user){
        if (confirmaLogin){
            UserHolder userHolder = UserHolder.getInstance();
            userHolder.setUser(user);
            try {
                FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("scenes/mailMainPage.fxml"));
                Parent root1 = (Parent) fxmlLoader.load();
                Stage stage = new Stage();
                stage.setTitle(user.toString().toLowerCase() + "@poomail.com.br");
                stage.setScene(new Scene(root1));
                stage.show();
                stage.getScene().getWindow().setOnHidden((event)-> {
                    this.scene.setVisible(true);
                    this.scene.getScene().getWindow().setOpacity(1);
                });
                this.scene.setVisible(false);
                this.scene.getScene().getWindow().setOpacity(0);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}
