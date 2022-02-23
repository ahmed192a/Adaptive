package application;
	
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;


public class Main extends Application {
	
	
    private static Stage primaryStage; // **Declare static Stage**    
    public static String Data; // **Declare static Stage**    

    private void setPrimaryStage(Stage stage) {
        Main.primaryStage = stage;
    }

    static public Stage getPrimaryStage() {
        return Main.primaryStage;
    }

	@Override
	public void start(Stage primaryStage) {
		try {
	        setPrimaryStage(primaryStage); // **Set the Stage**
			Parent root = FXMLLoader.load(getClass().getResource("Main.fxml")); 
			Scene scene = new Scene(root);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setScene(scene);
			primaryStage.setTitle("AUTOSAR Tool");
			Image icon = new Image("icon.png");
			primaryStage.getIcons().add(icon);
			primaryStage.show();
	
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
