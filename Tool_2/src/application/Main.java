package application;
	
import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;

public class Main extends Application {
	
	// **Declare static Stage**  
	private static Stage primaryStage; 
	private void setPrimaryStage(Stage stage) {Main.primaryStage = stage;}
	static public Stage getPrimaryStage() {return Main.primaryStage;}
	
	@Override
	public void start(Stage primaryStage) throws IOException{
		Parent root = FXMLLoader.load(getClass().getResource("Main.fxml")); 
		Scene scene = new Scene(root);
		setPrimaryStage(primaryStage);
		scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
		Image icon = new Image("icon.png");
		primaryStage.getIcons().add(icon);
		primaryStage.setResizable(false);
		primaryStage.setTitle("AUTOSAR Manifest Tool");
		primaryStage.setScene(scene);
		primaryStage.show();
	}
	
	public static void main(String[] args) {launch(args);}
}


