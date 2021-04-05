package poomail.controllers;

import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.ObservableList;
import javafx.event.EventType;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.BorderPane;
import poomail.classes.Email;
import poomail.classes.EmailData;
import poomail.classes.User;
import poomail.classes.UserHolder;

import java.util.EventListener;

public class ControllerMail {

    @FXML
    private BorderPane mainMailPage;
    @FXML
    private TextField fieldTitulo;
    @FXML
    private TextField fieldPara;
    @FXML
    private TextField fieldDe;
    @FXML
    private TextArea areaConteudo;
    @FXML
    private TableView<Email> tableEmails;
    @FXML
    private TableColumn tipoEntrada;

    private EmailData emailsCaixaEntrada;
    private EmailData emailsEnviados;
    private EmailData emailsLixeira;

    private User user;



    @FXML
    public void initialize (){
        this.emailsCaixaEntrada = new EmailData();
        this.emailsEnviados = new EmailData();
        this.emailsLixeira = new EmailData();
        this.user = UserHolder.getInstance().getUser();

        mainMailPage.requestFocus();

        populaEmail();


        tableEmails.setItems(emailsCaixaEntrada.getEmails());
        preencheEmail(emailsCaixaEntrada.getEmails().get(0));
    }








    @FXML
    public void novoEmail(){
        System.out.println("Novo email");
        fieldTitulo.setText("Opa, deu certo");
        fieldPara.setText(user.toString() + "@poomail.com");
    }

    @FXML
    public void tableClicked(){
        preencheEmail(tableEmails.getSelectionModel().getSelectedItem());
    }

    @FXML
    public void atualizarEmail(){
        System.out.println("Atualizar Email");
    }

    @FXML
    public void sairEmail(){
        mainMailPage.getScene().getWindow().hide();
    }

    @FXML
    public void caixaEntrada(){
        System.out.println("Caixa de entrada");
    }

    @FXML
    public void enviados(){
        System.out.println("Enviados");
    }

    @FXML
    public void lixeira(){
        System.out.println("Lixeira");
    }

    @FXML
    public void deletarEmail(){
        System.out.println("deletar");
    }

    private void changeFocus (){
        Platform.runLater( () -> mainMailPage.requestFocus());
    }

    public void preencheEmail(Email email){
        fieldPara.setText(user.toString());
        fieldDe.setText(email.getEmailDe());
        fieldTitulo.setText(email.getTitulo());
        areaConteudo.setWrapText(true);
        areaConteudo.setText(email.getConteudo());
    }


    private void populaEmail(){
        emailsCaixaEntrada.addEmail(new Email("JM", user.toString(), "Deu ruim", "Manda o nascimento pra brasilia"));
        emailsCaixaEntrada.addEmail(new Email("LI", user.toString(), "Desconto", "Existe desconto no serviço de manicure para quem tem 9 dedos?"));
        emailsCaixaEntrada.addEmail(new Email("Eneias", user.toString(), "WMD", "Pago R$ 500,00 pelo bombom"));
        emailsCaixaEntrada.addEmail(new Email("Trump", user.toString(), "Vendo bombom", "Vendo bombom R$ 250,00 ou 3 x 500,00"));
    }

}
