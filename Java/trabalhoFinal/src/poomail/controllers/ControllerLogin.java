package poomail.controllers;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import poomail.Main;
import poomail.data.User;
import poomail.holders.UserHolder;

import java.io.IOException;


public class ControllerLogin {

    @FXML
    private TextField loginField;
    @FXML
    private BorderPane scene;

    public ControllerLogin() {
        changeFocus();
    }

    @FXML
    public void initialize (){
        scene.requestFocus();
    }

    @FXML
    public void loginAction(){
        User user = new User(loginField.getText());
        if (user.validarLogin()) {
            openEmail(user);
        }else {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText(user.getLogErro());
            alert.show();
        }
    }

    @FXML
    public void textAction(){
        loginAction();
    }

    private void changeFocus (){
        Platform.runLater( () -> scene.requestFocus());
    }

    private void openEmail(User user){
        UserHolder userHolder = UserHolder.getInstance();
        userHolder.setUser(user);
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("scenes/mailMainPage.fxml"));
            Parent root1 = fxmlLoader.load();
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
