package poomail.classes;

public class User {
    private String username;
    private boolean isLoginValido;
    private String logErro;

    public User(String username) {
        this.username = username;
    }

    public void setUsername(String username){
        this.username = username;
    }

    @Override
    public String toString() {
        return this.username;
    }

    public boolean validarLogin (){
        String resposta = Talker.getInstance().login(this.username);
        String respotaValida = "{ \"okay\": { \"message\":\"login aceito” } }";
        String erroUJE = "{ \"error\": { \"message\":\"usuario ja existe.” } }";
        if (resposta.contains(respotaValida)){
            this.isLoginValido = true;
        }else {
            this.isLoginValido = false;
            if (resposta.contains(erroUJE)){
                this.logErro = "Usuario ja existe.";
            }else {
                this.logErro = "Usuario Invalido";
            }
        }
        return this.isLoginValido;
    }

    public boolean isLoginValido(){
        return this.isLoginValido;
    }

    public String getLogErro() {
        return logErro;
    }
}
